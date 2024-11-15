/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "buffer_pool_manager.h"

/**
 * @description: 从free_list或replacer中获取可替换的序列序frame_id
 * @return {bool} true: 成功找到可替换序列 ; false: 找不到可替换序列
 * @param {frame_id_t*} frame_id 序列序的frame_id指针，用于返回找到的可替换序列
 */
bool BufferPoolManager::find_victim_page(frame_id_t* frame_id) {
    // 判断free_list_中是否有空位
    if (!free_list_.empty()) {
        *frame_id = free_list_.front();
        free_list_.pop_front();
        return true;
    }
    // 当free_list_中没有空位时，通过replacer_来找到可替换的序列
    return replacer_->victim(frame_id);
}

/**
 * @description: 更新页面数据，如果为脏页则需写入磁盘，然后更新为新页面数据。更新页面元数据(data, is_dirty, page_id)和页表。
 * @param {Page*} page 写回页指针
 * @param {PageId} new_page_id 新的page_id
 * @param {frame_id_t} new_frame_id 新的frame_id
 */
void BufferPoolManager::update_page(Page *page, PageId new_page_id, frame_id_t new_frame_id) {
    // 如果页为脏，将其数据写回磁盘，然后把脏标志设置为false
    if (page->is_dirty()) {
        disk_manager_->write_page(page->get_page_id().fd, page->get_page_id().page_no, page->get_data(), PAGE_SIZE);
        page->is_dirty_ = false;
    }
    page->pin_count_ = 0;

    // 移除页表中的旧记录，并添加新的页数据
    page_table_.erase(page->get_page_id());
    page_table_[new_page_id] = new_frame_id;

    // 重置页内存，更新页的元数据
    page->reset_memory();
    pages_[new_frame_id].id_ = new_page_id;
    pages_[new_frame_id].is_dirty_ = false;
    pages_[new_frame_id].pin_count_ = 0;
}

/**
 * @description: 从缓冲池中获取指定的页。如果在页表中找到该页，则固定序列序，否则通过find_victim_page找到替换页。
 * @return {Page*} 获取的页或者为nullptr
 * @param {PageId} page_id 需要获取的PageId
 */
Page* BufferPoolManager::fetch_page(PageId page_id) {
    std::scoped_lock lock{latch_};

    // 在page_table_中查找目标页
    auto it = page_table_.find(page_id);
    if (it != page_table_.end()) {
        frame_id_t frame_id = it->second;
        replacer_->pin(frame_id);
        pages_[frame_id].pin_count_++;
        return pages_ + frame_id;
    }

    // 未找到目标页，并尝试获取可用的frame
    frame_id_t frame_id;
    if (!find_victim_page(&frame_id)) {
        return nullptr;
    }

    Page* victim_page = pages_ + frame_id;
    // 如果被替换的页是脏，将其写回磁盘
    update_page(victim_page, page_id, frame_id);

    // 从磁盘中读取目标页
    disk_manager_->read_page(page_id.fd, page_id.page_no, victim_page->get_data(), PAGE_SIZE);

    // 固定页，更新pin数据
    replacer_->pin(frame_id);
    victim_page->pin_count_++;
    return victim_page;
}

/**
 * @description: 取消已固定的页，更新pin_count和脏状态。
 * @return {bool} 若元实不存在或者无法取消固定，则返回false
 * @param {PageId} page_id 目标页的page_id
 * @param {bool} is_dirty 设置目标页是否脏。
 */
bool BufferPoolManager::unpin_page(PageId page_id, bool is_dirty) {
    std::scoped_lock lock{latch_};

    // 在page_table_中查找目标页
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }

    frame_id_t frame_id = it->second;
    Page& page = pages_[frame_id];

    // 如果pin_count已经为0，返回false
    if (page.pin_count_ <= 0) {
        return false;
    }

    // 减少pin_count，如果为0则解锁
    page.pin_count_--;
    if (page.pin_count_ == 0) {
        replacer_->unpin(frame_id);
    }

    // 更新脏状态
    if (is_dirty) {
        page.is_dirty_ = true;
    }
    return true;
}

/**
 * @description: 将指定的页写回磁盘，不考虑当前页是否正在被使用。
 * @return {bool} 若页表中没有目标页，则返回false
 * @param {PageId} page_id 目标页的page_id，不能为INVALID_PAGE_ID
 */
bool BufferPoolManager::flush_page(PageId page_id) {
    std::scoped_lock lock{latch_};

    // 在page_table_中查找目标页
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }

    frame_id_t frame_id = it->second;
    Page& page = pages_[frame_id];

    // 将页数据写回磁盘，并更新脏状态
    disk_manager_->write_page(page_id.fd, page_id.page_no, page.get_data(), PAGE_SIZE);
    page.is_dirty_ = false;
    return true;
}

/**
 * @description: 创建一个新的页，即在磁盘上新建一个页，并将它移动到缓冲池。
 * @return {Page*} 新创建的页，若失败则返回nullptr
 * @param {PageId*} page_id 新创建的页的page_id
 */
Page* BufferPoolManager::new_page(PageId* page_id) {
    std::scoped_lock lock{latch_};

    // 尝试获取可用的frame
    frame_id_t frame_id;
    if (!find_victim_page(&frame_id)) {
        return nullptr;
    }

    Page* new_page = pages_ + frame_id;

    // 在fd对应的文件中分配一个新的page_id
    page_id_t new_page_no = disk_manager_->allocate_page(page_id->fd);
    page_id->page_no = new_page_no;

    // 将应用的frame数据写回磁盘
    update_page(new_page, *page_id, frame_id);

    // 固定页，更新pin数据
    replacer_->pin(frame_id);
    new_page->pin_count_++;
    return new_page;
}

/**
 * @description: 从缓冲池中删除指定的页
 * @return {bool} 若页不存在或者删除成功返回true，否则返回false
 * @param {PageId} page_id 目标页
 */
bool BufferPoolManager::delete_page(PageId page_id) {
    std::scoped_lock lock{latch_};

    // 在page_table_中查找目标页，若不存在，直接返回true
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return true;
    }

    frame_id_t frame_id = it->second;
    Page* page = pages_ + frame_id;

    // 如果目标页的pin_count不为0，返回false
    if (page->pin_count_ != 0) {
        return false;
    }

    // 将目标页数据写回磁盘，重置页元数据，并移除页表中的记录
    disk_manager_->write_page(page->get_page_id().fd, page->get_page_id().page_no, page->get_data(), PAGE_SIZE);
    page_table_.erase(page_id);
    page->reset_memory();
    page->is_dirty_ = false;
    page->pin_count_ = 0;
    page->id_.page_no = INVALID_PAGE_ID;

    free_list_.push_back(frame_id);
    return true;
}

/**
 * @description: 将缓冲池中所有的页写回磁盘
 * @param {int} fd 文件控制令
 */
void BufferPoolManager::flush_all_pages(int fd) {
    std::scoped_lock lock{latch_};
    Page* page;
    for (size_t i = 0; i < pool_size_; i++) {
        page = pages_ + i;
        if ((page->get_page_id().fd == fd) && (page->get_page_id().page_no != INVALID_PAGE_ID)) {
            disk_manager_->write_page(fd, page->get_page_id().page_no, page->get_data(), PAGE_SIZE);
            page->is_dirty_ = false;
        }
    }
}

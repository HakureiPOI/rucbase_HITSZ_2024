/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "lru_replacer.h"
#include <algorithm>

LRUReplacer::LRUReplacer(size_t num_pages) : max_size_(num_pages) {}

LRUReplacer::~LRUReplacer() = default;

/**
 * @description: 使用LRU策略删除一个victim frame，并返回该frame的id
 * @param {frame_id_t*} frame_id 被移除的frame的id，如果没有frame被移除返回nullptr
 * @return {bool} 如果成功淘汰了一个页面则返回true，否则返回false
 */
bool LRUReplacer::victim(frame_id_t* frame_id) {
    // C++17 std::scoped_lock
    // 它能够避免死锁发生，其构造函数能够自动进行上锁操作，析构函数会对互斧量进行解锁操作，保证线程安全。
    std::scoped_lock lock{latch_};

    // 判断LRUlist_是否为空
    if (LRUlist_.empty()) {
        *frame_id = INVALID_FRAME_ID;
        return false;
    }
    // 移除最久未用的frame，更新frame_id
    *frame_id = LRUlist_.back();
    LRUlist_.pop_back();
    LRUhash_.erase(*frame_id);
    return true;
}

/**
 * @description: 固定指定的frame，即该页面无法被淘汰
 * @param {frame_id_t} frame_id 需要固定的frame的id
 */
void LRUReplacer::pin(frame_id_t frame_id) {
    std::scoped_lock lock{latch_};

    // 如果frame在LRUlist_中，削除它并更新相关数据
    auto it = LRUhash_.find(frame_id);
    if (it != LRUhash_.end()) {
        LRUlist_.erase(it->second);
        LRUhash_.erase(it);
    }
}

/**
 * @description: 取消固定一个frame，代表该页面可以被淘汰
 * @param {frame_id_t} frame_id 取消固定的frame的id
 */
void LRUReplacer::unpin(frame_id_t frame_id) {
    std::scoped_lock lock{latch_};

    // 如果frame不在LRUlist_中，将它添加到最前方
    if (LRUhash_.find(frame_id) == LRUhash_.end()) {
        LRUlist_.push_front(frame_id);
        LRUhash_[frame_id] = LRUlist_.begin();
    }
}

/**
 * @description: 获取当前replacer中可以被淘汰的页面数量
 * @return {size_t} 可淘汰的页面数量
 */
size_t LRUReplacer::Size() {
    std::scoped_lock lock{latch_};
    return LRUlist_.size();
}

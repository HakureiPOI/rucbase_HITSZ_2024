# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/lib/python3.10/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.10/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /content/rucbase-lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /content/rucbase-lab/build

# Include any dependencies generated for this target.
include src/test/CMakeFiles/regress_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/test/CMakeFiles/regress_test.dir/compiler_depend.make

# Include the progress variables for this target.
include src/test/CMakeFiles/regress_test.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/CMakeFiles/regress_test.dir/flags.make

src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o: src/test/CMakeFiles/regress_test.dir/flags.make
src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o: /content/rucbase-lab/src/test/regress/regress_test_main.cpp
src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o: src/test/CMakeFiles/regress_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/content/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o"
	cd /content/rucbase-lab/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o -MF CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o.d -o CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o -c /content/rucbase-lab/src/test/regress/regress_test_main.cpp

src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.i"
	cd /content/rucbase-lab/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /content/rucbase-lab/src/test/regress/regress_test_main.cpp > CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.i

src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.s"
	cd /content/rucbase-lab/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /content/rucbase-lab/src/test/regress/regress_test_main.cpp -o CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.s

src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.o: src/test/CMakeFiles/regress_test.dir/flags.make
src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.o: /content/rucbase-lab/src/test/regress/regress_test.cpp
src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.o: src/test/CMakeFiles/regress_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/content/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.o"
	cd /content/rucbase-lab/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.o -MF CMakeFiles/regress_test.dir/regress/regress_test.cpp.o.d -o CMakeFiles/regress_test.dir/regress/regress_test.cpp.o -c /content/rucbase-lab/src/test/regress/regress_test.cpp

src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/regress_test.dir/regress/regress_test.cpp.i"
	cd /content/rucbase-lab/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /content/rucbase-lab/src/test/regress/regress_test.cpp > CMakeFiles/regress_test.dir/regress/regress_test.cpp.i

src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/regress_test.dir/regress/regress_test.cpp.s"
	cd /content/rucbase-lab/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /content/rucbase-lab/src/test/regress/regress_test.cpp -o CMakeFiles/regress_test.dir/regress/regress_test.cpp.s

# Object files for target regress_test
regress_test_OBJECTS = \
"CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o" \
"CMakeFiles/regress_test.dir/regress/regress_test.cpp.o"

# External object files for target regress_test
regress_test_EXTERNAL_OBJECTS =

bin/regress_test: src/test/CMakeFiles/regress_test.dir/regress/regress_test_main.cpp.o
bin/regress_test: src/test/CMakeFiles/regress_test.dir/regress/regress_test.cpp.o
bin/regress_test: src/test/CMakeFiles/regress_test.dir/build.make
bin/regress_test: src/test/CMakeFiles/regress_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/content/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/regress_test"
	cd /content/rucbase-lab/build/src/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/regress_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/CMakeFiles/regress_test.dir/build: bin/regress_test
.PHONY : src/test/CMakeFiles/regress_test.dir/build

src/test/CMakeFiles/regress_test.dir/clean:
	cd /content/rucbase-lab/build/src/test && $(CMAKE_COMMAND) -P CMakeFiles/regress_test.dir/cmake_clean.cmake
.PHONY : src/test/CMakeFiles/regress_test.dir/clean

src/test/CMakeFiles/regress_test.dir/depend:
	cd /content/rucbase-lab/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /content/rucbase-lab /content/rucbase-lab/src/test /content/rucbase-lab/build /content/rucbase-lab/build/src/test /content/rucbase-lab/build/src/test/CMakeFiles/regress_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/test/CMakeFiles/regress_test.dir/depend


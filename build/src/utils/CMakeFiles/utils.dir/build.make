# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wujianchao5/project/my/lern-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wujianchao5/project/my/lern-cpp/build

# Include any dependencies generated for this target.
include src/utils/CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include src/utils/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include src/utils/CMakeFiles/utils.dir/flags.make

src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.o: src/utils/CMakeFiles/utils.dir/flags.make
src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.o: ../src/utils/threadpool/GroupedThreadPoolTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.o"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.o -c /Users/wujianchao5/project/my/lern-cpp/src/utils/threadpool/GroupedThreadPoolTest.cpp

src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.i"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wujianchao5/project/my/lern-cpp/src/utils/threadpool/GroupedThreadPoolTest.cpp > CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.i

src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.s"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wujianchao5/project/my/lern-cpp/src/utils/threadpool/GroupedThreadPoolTest.cpp -o CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.s

src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.o: src/utils/CMakeFiles/utils.dir/flags.make
src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.o: ../src/utils/threadpool/GroupedThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.o"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.o -c /Users/wujianchao5/project/my/lern-cpp/src/utils/threadpool/GroupedThreadPool.cpp

src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.i"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wujianchao5/project/my/lern-cpp/src/utils/threadpool/GroupedThreadPool.cpp > CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.i

src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.s"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wujianchao5/project/my/lern-cpp/src/utils/threadpool/GroupedThreadPool.cpp -o CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.s

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.o" \
"CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

src/utils/libutils.a: src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPoolTest.cpp.o
src/utils/libutils.a: src/utils/CMakeFiles/utils.dir/threadpool/GroupedThreadPool.cpp.o
src/utils/libutils.a: src/utils/CMakeFiles/utils.dir/build.make
src/utils/libutils.a: src/utils/CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libutils.a"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean_target.cmake
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/utils/CMakeFiles/utils.dir/build: src/utils/libutils.a

.PHONY : src/utils/CMakeFiles/utils.dir/build

src/utils/CMakeFiles/utils.dir/clean:
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : src/utils/CMakeFiles/utils.dir/clean

src/utils/CMakeFiles/utils.dir/depend:
	cd /Users/wujianchao5/project/my/lern-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wujianchao5/project/my/lern-cpp /Users/wujianchao5/project/my/lern-cpp/src/utils /Users/wujianchao5/project/my/lern-cpp/build /Users/wujianchao5/project/my/lern-cpp/build/src/utils /Users/wujianchao5/project/my/lern-cpp/build/src/utils/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/utils/CMakeFiles/utils.dir/depend


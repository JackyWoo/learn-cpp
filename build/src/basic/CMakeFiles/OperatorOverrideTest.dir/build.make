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
include src/basic/CMakeFiles/OperatorOverrideTest.dir/depend.make

# Include the progress variables for this target.
include src/basic/CMakeFiles/OperatorOverrideTest.dir/progress.make

# Include the compile flags for this target's objects.
include src/basic/CMakeFiles/OperatorOverrideTest.dir/flags.make

src/basic/CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.o: src/basic/CMakeFiles/OperatorOverrideTest.dir/flags.make
src/basic/CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.o: ../src/basic/operator/OperatorOverrideTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/basic/CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.o"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.o -c /Users/wujianchao5/project/my/lern-cpp/src/basic/operator/OperatorOverrideTest.cpp

src/basic/CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.i"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wujianchao5/project/my/lern-cpp/src/basic/operator/OperatorOverrideTest.cpp > CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.i

src/basic/CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.s"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wujianchao5/project/my/lern-cpp/src/basic/operator/OperatorOverrideTest.cpp -o CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.s

# Object files for target OperatorOverrideTest
OperatorOverrideTest_OBJECTS = \
"CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.o"

# External object files for target OperatorOverrideTest
OperatorOverrideTest_EXTERNAL_OBJECTS =

src/basic/OperatorOverrideTest: src/basic/CMakeFiles/OperatorOverrideTest.dir/operator/OperatorOverrideTest.cpp.o
src/basic/OperatorOverrideTest: src/basic/CMakeFiles/OperatorOverrideTest.dir/build.make
src/basic/OperatorOverrideTest: src/basic/CMakeFiles/OperatorOverrideTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OperatorOverrideTest"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OperatorOverrideTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/basic/CMakeFiles/OperatorOverrideTest.dir/build: src/basic/OperatorOverrideTest

.PHONY : src/basic/CMakeFiles/OperatorOverrideTest.dir/build

src/basic/CMakeFiles/OperatorOverrideTest.dir/clean:
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && $(CMAKE_COMMAND) -P CMakeFiles/OperatorOverrideTest.dir/cmake_clean.cmake
.PHONY : src/basic/CMakeFiles/OperatorOverrideTest.dir/clean

src/basic/CMakeFiles/OperatorOverrideTest.dir/depend:
	cd /Users/wujianchao5/project/my/lern-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wujianchao5/project/my/lern-cpp /Users/wujianchao5/project/my/lern-cpp/src/basic /Users/wujianchao5/project/my/lern-cpp/build /Users/wujianchao5/project/my/lern-cpp/build/src/basic /Users/wujianchao5/project/my/lern-cpp/build/src/basic/CMakeFiles/OperatorOverrideTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/basic/CMakeFiles/OperatorOverrideTest.dir/depend

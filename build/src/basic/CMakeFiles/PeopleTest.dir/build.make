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
include src/basic/CMakeFiles/PeopleTest.dir/depend.make

# Include the progress variables for this target.
include src/basic/CMakeFiles/PeopleTest.dir/progress.make

# Include the compile flags for this target's objects.
include src/basic/CMakeFiles/PeopleTest.dir/flags.make

src/basic/CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.o: src/basic/CMakeFiles/PeopleTest.dir/flags.make
src/basic/CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.o: ../src/basic/oop/PeopleTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/basic/CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.o"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.o -c /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/PeopleTest.cpp

src/basic/CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.i"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/PeopleTest.cpp > CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.i

src/basic/CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.s"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/PeopleTest.cpp -o CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.s

src/basic/CMakeFiles/PeopleTest.dir/oop/People.cpp.o: src/basic/CMakeFiles/PeopleTest.dir/flags.make
src/basic/CMakeFiles/PeopleTest.dir/oop/People.cpp.o: ../src/basic/oop/People.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/basic/CMakeFiles/PeopleTest.dir/oop/People.cpp.o"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PeopleTest.dir/oop/People.cpp.o -c /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/People.cpp

src/basic/CMakeFiles/PeopleTest.dir/oop/People.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PeopleTest.dir/oop/People.cpp.i"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/People.cpp > CMakeFiles/PeopleTest.dir/oop/People.cpp.i

src/basic/CMakeFiles/PeopleTest.dir/oop/People.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PeopleTest.dir/oop/People.cpp.s"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/People.cpp -o CMakeFiles/PeopleTest.dir/oop/People.cpp.s

src/basic/CMakeFiles/PeopleTest.dir/oop/Man.cpp.o: src/basic/CMakeFiles/PeopleTest.dir/flags.make
src/basic/CMakeFiles/PeopleTest.dir/oop/Man.cpp.o: ../src/basic/oop/Man.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/basic/CMakeFiles/PeopleTest.dir/oop/Man.cpp.o"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PeopleTest.dir/oop/Man.cpp.o -c /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/Man.cpp

src/basic/CMakeFiles/PeopleTest.dir/oop/Man.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PeopleTest.dir/oop/Man.cpp.i"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/Man.cpp > CMakeFiles/PeopleTest.dir/oop/Man.cpp.i

src/basic/CMakeFiles/PeopleTest.dir/oop/Man.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PeopleTest.dir/oop/Man.cpp.s"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && /usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wujianchao5/project/my/lern-cpp/src/basic/oop/Man.cpp -o CMakeFiles/PeopleTest.dir/oop/Man.cpp.s

# Object files for target PeopleTest
PeopleTest_OBJECTS = \
"CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.o" \
"CMakeFiles/PeopleTest.dir/oop/People.cpp.o" \
"CMakeFiles/PeopleTest.dir/oop/Man.cpp.o"

# External object files for target PeopleTest
PeopleTest_EXTERNAL_OBJECTS =

src/basic/PeopleTest: src/basic/CMakeFiles/PeopleTest.dir/oop/PeopleTest.cpp.o
src/basic/PeopleTest: src/basic/CMakeFiles/PeopleTest.dir/oop/People.cpp.o
src/basic/PeopleTest: src/basic/CMakeFiles/PeopleTest.dir/oop/Man.cpp.o
src/basic/PeopleTest: src/basic/CMakeFiles/PeopleTest.dir/build.make
src/basic/PeopleTest: src/basic/CMakeFiles/PeopleTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wujianchao5/project/my/lern-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable PeopleTest"
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PeopleTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/basic/CMakeFiles/PeopleTest.dir/build: src/basic/PeopleTest

.PHONY : src/basic/CMakeFiles/PeopleTest.dir/build

src/basic/CMakeFiles/PeopleTest.dir/clean:
	cd /Users/wujianchao5/project/my/lern-cpp/build/src/basic && $(CMAKE_COMMAND) -P CMakeFiles/PeopleTest.dir/cmake_clean.cmake
.PHONY : src/basic/CMakeFiles/PeopleTest.dir/clean

src/basic/CMakeFiles/PeopleTest.dir/depend:
	cd /Users/wujianchao5/project/my/lern-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wujianchao5/project/my/lern-cpp /Users/wujianchao5/project/my/lern-cpp/src/basic /Users/wujianchao5/project/my/lern-cpp/build /Users/wujianchao5/project/my/lern-cpp/build/src/basic /Users/wujianchao5/project/my/lern-cpp/build/src/basic/CMakeFiles/PeopleTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/basic/CMakeFiles/PeopleTest.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pelmeshka127/Desktop/ILab/RedBlackTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build

# Include any dependencies generated for this target.
include level1/tests/ete/CMakeFiles/rbtreetest1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include level1/tests/ete/CMakeFiles/rbtreetest1.dir/compiler_depend.make

# Include the progress variables for this target.
include level1/tests/ete/CMakeFiles/rbtreetest1.dir/progress.make

# Include the compile flags for this target's objects.
include level1/tests/ete/CMakeFiles/rbtreetest1.dir/flags.make

level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o: level1/tests/ete/CMakeFiles/rbtreetest1.dir/flags.make
level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o: /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level1/tests/ete/rbtreetest.cpp
level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o: level1/tests/ete/CMakeFiles/rbtreetest1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o -MF CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o.d -o CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o -c /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level1/tests/ete/rbtreetest.cpp

level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.i"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level1/tests/ete/rbtreetest.cpp > CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.i

level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.s"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level1/tests/ete/rbtreetest.cpp -o CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.s

# Object files for target rbtreetest1
rbtreetest1_OBJECTS = \
"CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o"

# External object files for target rbtreetest1
rbtreetest1_EXTERNAL_OBJECTS =

level1/tests/ete/rbtreetest1: level1/tests/ete/CMakeFiles/rbtreetest1.dir/rbtreetest.cpp.o
level1/tests/ete/rbtreetest1: level1/tests/ete/CMakeFiles/rbtreetest1.dir/build.make
level1/tests/ete/rbtreetest1: /usr/local/lib/libgtest.a
level1/tests/ete/rbtreetest1: level1/tests/ete/CMakeFiles/rbtreetest1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rbtreetest1"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rbtreetest1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
level1/tests/ete/CMakeFiles/rbtreetest1.dir/build: level1/tests/ete/rbtreetest1
.PHONY : level1/tests/ete/CMakeFiles/rbtreetest1.dir/build

level1/tests/ete/CMakeFiles/rbtreetest1.dir/clean:
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete && $(CMAKE_COMMAND) -P CMakeFiles/rbtreetest1.dir/cmake_clean.cmake
.PHONY : level1/tests/ete/CMakeFiles/rbtreetest1.dir/clean

level1/tests/ete/CMakeFiles/rbtreetest1.dir/depend:
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pelmeshka127/Desktop/ILab/RedBlackTree /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level1/tests/ete /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level1/tests/ete/CMakeFiles/rbtreetest1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : level1/tests/ete/CMakeFiles/rbtreetest1.dir/depend


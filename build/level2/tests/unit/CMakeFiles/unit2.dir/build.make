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
include level2/tests/unit/CMakeFiles/unit2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include level2/tests/unit/CMakeFiles/unit2.dir/compiler_depend.make

# Include the progress variables for this target.
include level2/tests/unit/CMakeFiles/unit2.dir/progress.make

# Include the compile flags for this target's objects.
include level2/tests/unit/CMakeFiles/unit2.dir/flags.make

level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.o: level2/tests/unit/CMakeFiles/unit2.dir/flags.make
level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.o: /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level2/tests/unit/unit.cpp
level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.o: level2/tests/unit/CMakeFiles/unit2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.o"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.o -MF CMakeFiles/unit2.dir/unit.cpp.o.d -o CMakeFiles/unit2.dir/unit.cpp.o -c /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level2/tests/unit/unit.cpp

level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit2.dir/unit.cpp.i"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level2/tests/unit/unit.cpp > CMakeFiles/unit2.dir/unit.cpp.i

level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit2.dir/unit.cpp.s"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level2/tests/unit/unit.cpp -o CMakeFiles/unit2.dir/unit.cpp.s

# Object files for target unit2
unit2_OBJECTS = \
"CMakeFiles/unit2.dir/unit.cpp.o"

# External object files for target unit2
unit2_EXTERNAL_OBJECTS =

level2/tests/unit/unit2: level2/tests/unit/CMakeFiles/unit2.dir/unit.cpp.o
level2/tests/unit/unit2: level2/tests/unit/CMakeFiles/unit2.dir/build.make
level2/tests/unit/unit2: /usr/local/lib/libgtest.a
level2/tests/unit/unit2: level2/tests/unit/CMakeFiles/unit2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable unit2"
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
level2/tests/unit/CMakeFiles/unit2.dir/build: level2/tests/unit/unit2
.PHONY : level2/tests/unit/CMakeFiles/unit2.dir/build

level2/tests/unit/CMakeFiles/unit2.dir/clean:
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit && $(CMAKE_COMMAND) -P CMakeFiles/unit2.dir/cmake_clean.cmake
.PHONY : level2/tests/unit/CMakeFiles/unit2.dir/clean

level2/tests/unit/CMakeFiles/unit2.dir/depend:
	cd /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pelmeshka127/Desktop/ILab/RedBlackTree /Users/pelmeshka127/Desktop/ILab/RedBlackTree/level2/tests/unit /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit /Users/pelmeshka127/Desktop/ILab/RedBlackTree/build/level2/tests/unit/CMakeFiles/unit2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : level2/tests/unit/CMakeFiles/unit2.dir/depend


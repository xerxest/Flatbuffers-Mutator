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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build

# Include any dependencies generated for this target.
include CMakeFiles/FlatBufferMutator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FlatBufferMutator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FlatBufferMutator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FlatBufferMutator.dir/flags.make

CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o: CMakeFiles/FlatBufferMutator.dir/flags.make
CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o: /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/src/mutator/mutator.cpp
CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o: CMakeFiles/FlatBufferMutator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o -MF CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o.d -o CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o -c /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/src/mutator/mutator.cpp

CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/src/mutator/mutator.cpp > CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.i

CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/src/mutator/mutator.cpp -o CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.s

# Object files for target FlatBufferMutator
FlatBufferMutator_OBJECTS = \
"CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o"

# External object files for target FlatBufferMutator
FlatBufferMutator_EXTERNAL_OBJECTS =

FlatBufferMutator: CMakeFiles/FlatBufferMutator.dir/src/mutator/mutator.cpp.o
FlatBufferMutator: CMakeFiles/FlatBufferMutator.dir/build.make
FlatBufferMutator: /usr/local/lib/libflatbuffers.a
FlatBufferMutator: CMakeFiles/FlatBufferMutator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FlatBufferMutator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FlatBufferMutator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FlatBufferMutator.dir/build: FlatBufferMutator
.PHONY : CMakeFiles/FlatBufferMutator.dir/build

CMakeFiles/FlatBufferMutator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FlatBufferMutator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FlatBufferMutator.dir/clean

CMakeFiles/FlatBufferMutator.dir/depend:
	cd /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build /Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/build/CMakeFiles/FlatBufferMutator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/FlatBufferMutator.dir/depend


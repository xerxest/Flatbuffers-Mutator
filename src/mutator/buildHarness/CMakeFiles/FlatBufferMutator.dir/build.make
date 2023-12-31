# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /xerg/src/mutator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /xerg/src/mutator/buildHarness

# Include any dependencies generated for this target.
include CMakeFiles/FlatBufferMutator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FlatBufferMutator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FlatBufferMutator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FlatBufferMutator.dir/flags.make

CMakeFiles/FlatBufferMutator.dir/harness.cpp.o: CMakeFiles/FlatBufferMutator.dir/flags.make
CMakeFiles/FlatBufferMutator.dir/harness.cpp.o: ../harness.cpp
CMakeFiles/FlatBufferMutator.dir/harness.cpp.o: CMakeFiles/FlatBufferMutator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/xerg/src/mutator/buildHarness/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FlatBufferMutator.dir/harness.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FlatBufferMutator.dir/harness.cpp.o -MF CMakeFiles/FlatBufferMutator.dir/harness.cpp.o.d -o CMakeFiles/FlatBufferMutator.dir/harness.cpp.o -c /xerg/src/mutator/harness.cpp

CMakeFiles/FlatBufferMutator.dir/harness.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlatBufferMutator.dir/harness.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /xerg/src/mutator/harness.cpp > CMakeFiles/FlatBufferMutator.dir/harness.cpp.i

CMakeFiles/FlatBufferMutator.dir/harness.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlatBufferMutator.dir/harness.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /xerg/src/mutator/harness.cpp -o CMakeFiles/FlatBufferMutator.dir/harness.cpp.s

# Object files for target FlatBufferMutator
FlatBufferMutator_OBJECTS = \
"CMakeFiles/FlatBufferMutator.dir/harness.cpp.o"

# External object files for target FlatBufferMutator
FlatBufferMutator_EXTERNAL_OBJECTS =

FlatBufferMutator: CMakeFiles/FlatBufferMutator.dir/harness.cpp.o
FlatBufferMutator: CMakeFiles/FlatBufferMutator.dir/build.make
FlatBufferMutator: /usr/local/lib/libflatbuffers.a
FlatBufferMutator: CMakeFiles/FlatBufferMutator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/xerg/src/mutator/buildHarness/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FlatBufferMutator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FlatBufferMutator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FlatBufferMutator.dir/build: FlatBufferMutator
.PHONY : CMakeFiles/FlatBufferMutator.dir/build

CMakeFiles/FlatBufferMutator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FlatBufferMutator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FlatBufferMutator.dir/clean

CMakeFiles/FlatBufferMutator.dir/depend:
	cd /xerg/src/mutator/buildHarness && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /xerg/src/mutator /xerg/src/mutator /xerg/src/mutator/buildHarness /xerg/src/mutator/buildHarness /xerg/src/mutator/buildHarness/CMakeFiles/FlatBufferMutator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FlatBufferMutator.dir/depend


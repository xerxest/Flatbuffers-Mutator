# # CMakeLists.txt

# cmake_minimum_required(VERSION 3.10)  # You can adjust the version as needed

# project(FlatBufferMutator)

# # Specify the location of FlatbuffersConfig.cmake
# set(flatbuffers_DIR "/Users/xerxes/Documents/Coms_413/flatbuffers/Flatbuffers-Mutator/flatbuffers/CMake")

# # Find FlatBuffers
# find_package(flatbuffers REQUIRED)

# # Get all source files in the 'src' directory.
# file(GLOB SOURCE_FILES "src/mutator/*.cpp")

# # Create the executable
# add_executable(FlatBufferMutator ${SOURCE_FILES})

# # Include directories for Flatbuffers
# target_include_directories(FlatBufferMutator PRIVATE ${FLATBUFFERS_INCLUDE_DIRS})

# message(STATUS "MySymbol value: ${SOURCE_FILES}")

# # Link FlatBuffers library
# target_link_libraries(FlatBufferMutator PRIVATE flatbuffers)


# cmake_minimum_required(VERSION 3.0)
# project(FlatBufferMutator)

# set(CMAKE_CXX_COMPILER g++)

# # Specify the path to Flatbuffers installation
# set(FLATBUFFERS_INSTALL_DIR "/usr/local/include/")

# # Add the executable target
# add_executable(FlatBufferMutator src/mutator/mutator.cpp)

# # Specify the include directories for Flatbuffers
# target_include_directories(FlatBufferMutator PRIVATE ${FLATBUFFERS_INSTALL_DIR})

# # Specify the link directories for Flatbuffers
# link_directories(${FLATBUFFERS_INSTALL_DIR}/lib)

# # # Link libraries to the target
# # target_link_libraries(FlatBufferMutator PRIVATE flatbuffers)

# target_link_libraries(FlatBufferMutator PRIVATE /usr/local/lib/libflatbuffers.a)


cmake_minimum_required(VERSION 3.0)
project(FlatBufferMutator)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 11)

# Specify the path to Flatbuffers installation
set(FLATBUFFERS_INSTALL_DIR "/usr/local")

# Add the executable target
add_executable(FlatBufferMutator src/mutator/mutator.cpp)

# Specify the include directories for Flatbuffers
target_include_directories(FlatBufferMutator PRIVATE ${FLATBUFFERS_INSTALL_DIR}/include)

# Link libraries to the target
target_link_libraries(FlatBufferMutator PRIVATE /usr/local/lib/libflatbuffers.a)

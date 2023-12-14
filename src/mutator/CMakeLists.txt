cmake_minimum_required(VERSION 3.0)
project(FlatBufferHarness)

set(CMAKE_CXX_COMPILER afl-c++)

set(CMAKE_CXX_STANDARD 11)

# Specify the path to Flatbuffers installation
set(FLATBUFFERS_INSTALL_DIR "/usr/local")

# Add the executable target
add_executable(FlatBufferHarness BasicTest.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Specify the include directories for Flatbuffers
target_include_directories(FlatBufferHarness PRIVATE ${FLATBUFFERS_INSTALL_DIR}/include)

# Link libraries to the target
target_link_libraries(FlatBufferHarness PRIVATE /usr/local/lib/libflatbuffers.a)
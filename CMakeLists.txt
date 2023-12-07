cmake_minimum_required(VERSION 3.0)
project(FlatBufferMutator)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)

# Specify the path to Flatbuffers installation
set(FLATBUFFERS_INSTALL_DIR "/usr/local")
set(AFL_INSTALL_DIR "aflplusplus/include")

# Set the shared library suffix explicitly
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

# Add the library target
add_library(FlatBufferMutator SHARED
    src/mutator/mutator.cpp
)

# Specify the include directories for Flatbuffers
target_include_directories(FlatBufferMutator 
    PRIVATE 
    ${FLATBUFFERS_INSTALL_DIR}/include
    ${AFL_INSTALL_DIR}
)

# Link libraries to the target
target_link_libraries(FlatBufferMutator PRIVATE /usr/local/lib/libflatbuffers.a)

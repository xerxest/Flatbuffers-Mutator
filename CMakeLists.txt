cmake_minimum_required(VERSION 3.10)
project(MyFlatbufferProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find AFLplusplus (replace afl++-clang++ with your AFLplusplus compiler)
find_program(AFL_COMPILER NAMES afl++-clang++ REQUIRED)

# Add the src directory containing your main program and source files
add_subdirectory(src)

# Specify the output directory for the built executable (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include the seed_inputs directory in the build
file(COPY seed_inputs DESTINATION ${CMAKE_BINARY_DIR})


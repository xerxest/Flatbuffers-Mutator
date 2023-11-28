# Define the sources for your main program
set(SOURCES
    main.cpp            # Replace with your main program source file
    flatMutator.cpp      # Your custom mutator source file
)

# Create an executable target for your program
add_executable(my_flatbuffer_program ${SOURCES})

# Link AFLplusplus (replace afl++-clang++ with your AFLplusplus compiler)
target_link_libraries(my_flatbuffer_program PRIVATE afl++-clang++)

# If you have additional dependencies, add them here
# target_link_libraries(my_flatbuffer_program PRIVATE other_dependency)

# Specify any include directories if needed
# target_include_directories(my_flatbuffer_program PRIVATE /path/to/headers)

# Optionally, set compiler flags or other build options
# target_compile_options(my_flatbuffer_program PRIVATE -Wall -O2)


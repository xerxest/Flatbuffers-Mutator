#include <iostream>
#include <fstream>
#include <flatbuffers/flatbuffers.h>
#include "TestSchema_generated.h"  // Replace with the actual generated Flatbuffer header

int main() {
    // Load a Flatbuffer binary file as input
    const char* input_filename = "input.bin";  // Replace with the name of your input file
    std::ifstream input_file(input_filename, std::ios::binary);
    
    if (!input_file) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    // Read the Flatbuffer binary data from the file
    input_file.seekg(0, std::ios::end);
    size_t input_size = input_file.tellg();
    input_file.seekg(0, std::ios::beg);

    std::vector<char> input_data(input_size);
    input_file.read(input_data.data(), input_size);
    input_file.close();

    // Parse the Flatbuffer data
    const uint8_t* flatbuffer_data = reinterpret_cast<const uint8_t*>(input_data.data());
    const auto* flatbuffer_object = TestSchema::GetYourFlatbufferRoot(flatbuffer_data);

    // Access and manipulate Flatbuffer fields
    std::cout << "Field1: " << flatbuffer_object->field1() << std::endl;
    std::cout << "Field2: " << flatbuffer_object->field2()->c_str() << std::endl;

    // Add your program logic here to work with the Flatbuffer data
    // Example: Test a condition based on field values
    if (flatbuffer_object->field1() == 42) {
        std::cout << "Field1 is 42. Performing some action..." << std::endl;
        // Add your action or test logic here
    } else {
        std::cout << "Field1 is not 42. Performing a different action..." << std::endl;
        // Add a different action or test logic here
    }

    // Example: Iterate through a vector in the Flatbuffer
    const auto* vector_of_ints = flatbuffer_object->vector_of_ints();
    std::cout << "Vector of Integers:" << std::endl;
    for (size_t i = 0; i < vector_of_ints->size(); ++i) {
        std::cout << "Element " << i << ": " << vector_of_ints->Get(i) << std::endl;
        
        // Add your logic to process individual elements of the vector here
        int element_value = vector_of_ints->Get(i);
        if (element_value > 10) {
            std::cout << "Element " << i << " is greater than 10. Performing some action..." << std::endl;
            // Add your action or test logic for this element here
        } else {
            std::cout << "Element " << i << " is not greater than 10. Performing a different action..." << std::endl;
            // Add a different action or test logic for this element here
        }
    }

    return 0;
}


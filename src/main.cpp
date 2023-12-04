#include <iostream>
#include <fstream>
#include <flatbuffers/flatbuffers.h>
#include "TestSchema_generated.h" // Use the generated header for your root type

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
    const TestSchema::TestObject* flatbuffer_object = TestSchema::GetRootAsTestObject(flatbuffer_data);

    // Access and manipulate Flatbuffer fields
    std::cout << "ID: " << flatbuffer_object->id() << std::endl;
    std::cout << "Name: " << flatbuffer_object->name()->c_str() << std::endl;

    // Accessing the 'data' field as a vector of bytes
    const flatbuffers::Vector<uint8_t>* data_vector = flatbuffer_object->data();
    std::cout << "Data: ";
    for (flatbuffers::uoffset_t i = 0; i < data_vector->size(); ++i) {
        std::cout << static_cast<int>(data_vector->Get(i)) << " ";
    }
    std::cout << std::endl;

    // Add your program logic here to work with the Flatbuffer data

    return 0;
}

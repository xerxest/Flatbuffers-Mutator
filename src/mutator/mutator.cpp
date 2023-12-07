#include "flatbuffers/flatbuffers.h"
#include "message_generated.h"
#include <iostream>
#include <fstream>
#include <vector>

void mutateFlatBufferInMemory(const std::string& inputFilename) {
    // Read the binary file in smaller chunks to avoid excessive memory usage
    constexpr size_t buffer_size = 4096; // Adjust the buffer size as needed
    std::vector<char> buffer(buffer_size);

    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening input file: " << inputFilename << std::endl;
        return;
    }

    flatbuffers::FlatBufferBuilder builder;

    while (!inputFile.eof()) {
        // Read a chunk of data from the input file
        inputFile.read(buffer.data(), buffer_size);
        std::streamsize bytesRead = inputFile.gcount();

        if (bytesRead > 0) {
            // Access the data
            auto message = Example::GetMessage(buffer.data());

            // Mutate the data - for example, append something to the string
            std::string newText = std::string(message->text()->c_str()) + " Mutated";

            // Clear the builder and continue to the next chunk
            builder.Clear();
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1; // Return an error code
    }

    const std::string inputFilename = argv[1];

    mutateFlatBufferInMemory(inputFilename);
    return 0;
}

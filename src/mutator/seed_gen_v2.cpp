#include "flatbuffers/flatbuffers.h"
#include "message_generated.h"
#include <iostream>
#include <fstream>

int main() {
    // Create a FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder;

    // Create a message with some text
    auto text = builder.CreateString("Hello, World!");

    // Create a Message using the schema
    auto message = Example::CreateMessage(builder, text);

    // Finish building the FlatBuffer
    builder.Finish(message);

    // Write the FlatBuffer to a file
    std::ofstream outputFile("valid_seed.fb", std::ios::binary);
    if (!outputFile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize())) {
        std::cerr << "Error writing seed file" << std::endl;
        return 1;
    }

    return 0;
}


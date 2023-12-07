#include "flatbuffers/flatbuffers.h"
#include "message_generated.h" // Your generated header
#include <iostream>
#include <fstream>

void createFlatBuffer(const std::string& text, const std::string& outputFilename) {
    flatbuffers::FlatBufferBuilder builder;
    auto textOffset = builder.CreateString(text);
    auto message = Example::CreateMessage(builder, textOffset);
    builder.Finish(message);

    std::ofstream outputFile(outputFilename, std::ios::binary);
    outputFile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize());
}

int main() {
    createFlatBuffer("Initial test message", "initial_test.fb");
    return 0;
}


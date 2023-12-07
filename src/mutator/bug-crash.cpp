#include "flatbuffers/flatbuffers.h"
#include "message_generated.h"
#include <fstream>

int main() {
    flatbuffers::FlatBufferBuilder builder;
    auto textOffset = builder.CreateString("Initial test message");
    auto message = Example::CreateMessage(builder, textOffset);
    builder.Finish(message);

    // Simulate a corrupted file by modifying the size in the buffer
    uint8_t* data = builder.GetBufferPointer();
    uint32_t size = builder.GetSize();

    // Make the size field in the buffer invalid (larger than actual size)
    data[size] = 0xAA;
    data[size + 1] = 0xBB;
    data[size + 2] = 0xCC;
    data[size + 3] = 0xDD;

    // Write the modified buffer to a file
    std::ofstream outputFile("corrupted_message.fb", std::ios::binary);
    outputFile.write(reinterpret_cast<const char*>(data), size + 4);

    return 0;
}


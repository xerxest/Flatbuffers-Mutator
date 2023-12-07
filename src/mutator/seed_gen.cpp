#include "flatbuffers/flatbuffers.h"
#include "message_generated.h" // Your generated header
#include <fstream>

int main() {
    flatbuffers::FlatBufferBuilder builder;

    // Create an empty message
    auto emptyMessage = Example::CreateMessage(builder);
    builder.Finish(emptyMessage);
    std::ofstream emptyFile("seed_empty.fb", std::ios::binary);
    emptyFile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize());
    emptyFile.close();
    builder.Clear();

    // Create a message with some text data
    auto text = builder.CreateString("Seed data for fuzzing");
    auto message = Example::CreateMessage(builder, text);
    builder.Finish(message);
    std::ofstream basicFile("seed_basic.fb", std::ios::binary);
    basicFile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize());
    basicFile.close();
    builder.Clear();

    // Create another variation of seed file here if needed

    return 0;
}


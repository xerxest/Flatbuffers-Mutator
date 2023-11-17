
#include <iostream>
#include "hello_world_generated.h"

int main() {
  // Create a FlatBuffer builder
  flatbuffers::FlatBufferBuilder builder;

  // Create a message with the text "Hello, World!"
  auto message = HelloWorld::CreateMessage(builder, builder.CreateString("Hello, World!"));

  // Finish building the FlatBuffer
  builder.Finish(message);

  // Access the FlatBuffer data
  const uint8_t* bufferPointer = builder.GetBufferPointer();
  const size_t bufferSize = builder.GetSize();

  // Assuming you want to do something with the buffer (send over the network, write to a file, etc.)
  // For this example, we'll just print the string.

  // Access the root of the FlatBuffer
  auto root = HelloWorld::GetMessage(bufferPointer);

  // Access the string field and print it
  std::cout << "Received message: " << root->text()->str() << std::endl;

  return 0;
}


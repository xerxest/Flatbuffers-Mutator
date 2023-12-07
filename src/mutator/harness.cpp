#include <stdio.h>
#include <string.h>
#include <cassert>

#include "flatbuffers/flatbuffers.h"
#include "message_generated.h"

int main(int argc, char *argv[]) {
  char str[6];
  fgets(str, sizeof(str), stdin);

  if (argc != 2) {
    fprintf(stderr, "Usage: %s input.fb\n", argv[0]);
    return 1;
  }

  const char *inputFilename = argv[1];
  FILE *inputFile = fopen(inputFilename, "rb");

  if (!inputFile) {
    fprintf(stderr, "Error opening input file: %s\n", inputFilename);
    return 1;
  }

  int zero = 0;
  // Introduce an out-of-bounds access
  flatbuffers::FlatBufferBuilder builder;
  auto text = builder.CreateString("Hello, World!");
  auto message = Example::CreateMessage(builder, text);
  builder.Finish(message);
  const uint8_t *data = builder.GetBufferPointer();
  uint32_t size = builder.GetSize();
  
  // Check if size is valid
  if (size < sizeof(Example::Message)) {
    fprintf(stderr, "Invalid .fb file size\n");
    return 1;
  }

  // Access an out-of-bounds index of the data
  if (data[size + 1] == 'A') {
    // This will trigger a crash due to out-of-bounds access
    assert(false);
  }

  fclose(inputFile);

  return 0;
}

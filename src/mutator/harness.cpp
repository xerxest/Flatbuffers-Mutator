#include "flatbuffers/flatbuffers.h"
#include "test_generated.h"
#include <iostream>
#include <vector>
#include <fstream>

int main() {

    std::vector<uint8_t> buffer;
    uint8_t byte;

    while (std::cin >> byte) {
        buffer.push_back(byte);
    }

    // std::ofstream outputFile("debug.txt", std::ios::trunc);

    // if (!outputFile.is_open()) {
    //     std::cerr << "Error: Unable to open the file." << std::endl;
    //     return 1;
    // }

    auto monster = MyGame::GetMonster(buffer.data());

    // if(monster->hp() == 1)
    // {
    //   assert(false);
    // }

    // // Append the text to the file
    // outputFile.write(reinterpret_cast<char*>(buffer.data()), 1544);

    // // Close the file
    // outputFile.close();

    return 0;
}
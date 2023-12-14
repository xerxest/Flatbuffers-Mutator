#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "test_generated.h"


int main(int argc, char* argv[]) {

    std::ifstream inputFile("outFlatbuf.bfbs");

    if (!inputFile.is_open()) {
        assert(false);
        return 1;
    }

    std::ostringstream fileContentStream;
    fileContentStream << inputFile.rdbuf();
    std::string fileContent = fileContentStream.str();

    auto monster = MyGame::GetMonster(fileContent.data());

    if(monster->hp() > 1000 && monster->hp() < 2000)
    {
      assert(false);
    }

    inputFile.close();

    return 0;
}

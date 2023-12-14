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

    char monsterName[20];
    std::strncpy(monsterName, monster->name()->c_str(), monster->name()->size() * sizeof(char));

    // May cause an segfault
    printf("%s\n", monsterName);

    inputFile.close();

    return 0;
}

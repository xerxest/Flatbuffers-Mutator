#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "test_generated.h"


int main(int argc, char* argv[]) {
    // Check if a file path is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        assert(false);
        return 1; // Return an error code
    }

    // Get the file path from the command-line arguments
    std::string filePath = argv[1];

    // Open the file
    std::ifstream inputFile("debug.txt");

    std::ofstream outputFile("debugTest.txt", std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        assert(false);
        return 1;
    }

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        assert(false);
        std::cerr << "Error: Unable to open the file '" << filePath << "'" << std::endl;
        return 1; // Return an error code
    }

    std::ostringstream fileContentStream;
    fileContentStream << inputFile.rdbuf();
    std::string fileContent = fileContentStream.str();

    auto monster = MyGame::GetMonster(fileContent.data());

    char buffer[5];
    strncpy(buffer, monster->name());
    printf("%s\n", buffer);

    outputFile.close();
    inputFile.close();

    return 0;
}

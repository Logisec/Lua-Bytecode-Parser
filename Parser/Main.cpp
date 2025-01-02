/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: Main.hpp
* Description: This is the main entry point for the program.
* 
*/
#include "PrettyPrint.hpp"
#include "Deserializer.hpp"
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    const char* inputFile = argv[1];
    std::ifstream file(inputFile, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << inputFile << std::endl;
        return 1;
    }

    std::vector<uint8_t> bytecode(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    try {
        Deserializer deserializer(bytecode);
        auto [header, proto] = deserializer.Parse();

        PrintHeader(header);
        PrintPrototype(proto);    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

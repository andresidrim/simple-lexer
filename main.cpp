/* GCC VERSION 13.2.0 */

/*

Instructions to run

g++ main.cpp lexer.cpp -o main
./main ./examples/input.txt

*/

#include <iostream>
#include <string>
#include <fstream>
#include "include/lexer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide your input file path. Ex: ./main input.txt\n";
        return 1;
    }

    if (argc < 3) {
        std::cerr << "Please provide your output file path. Ex: ./main output.txt\n";
        return 1;
    }


    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Could not open file `" << argv[1] << "`\n";
        return 1;
    }

    std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    inputFile.close();

    Lexer lexer;
    lexer.tokenize(fileContents);
    lexer.writeTokensToFile(argv[2]);

    return 0;
}
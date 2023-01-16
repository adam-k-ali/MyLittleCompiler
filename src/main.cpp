#include <iostream>
#include "FileMap.h"
#include "Token.h"
#include "Scanner.h"

int main() {
    FileMap file("../resources/Sample.b");

    // Print the first line
    for (char *c = file.begin(); c != file.end(); ++c) {
        if (*c == '\r') {
            std::cout << std::endl;
            break;
        }
        std::cout << *c;
    }
    std::cout << std::endl;

    // Tokenize the file
    Scanner scanner(file.begin(), file.end());

    // Print the tokens
    std::cout << "[";
    while(scanner.current() != scanner.end()) {
        std::cout << tokenToString(scanner.read());
        if (scanner.current() != scanner.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}

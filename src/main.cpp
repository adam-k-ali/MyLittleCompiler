#include <iostream>
#include "FileMap.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"


int main() {
    FileMap file("../resources/Sample.b");

    // Tokenize the file
    Scanner scanner(file.begin(), file.end());

    Parser parser(scanner.getTokens());
    Expr *expr = parser.parse();
    if (expr != nullptr) {
        std::cout << "Expression: \"" << expr->toString() << "\""<< std::endl;
    } else {
        std::cout << "Error" << std::endl;
    }
    return 0;
}

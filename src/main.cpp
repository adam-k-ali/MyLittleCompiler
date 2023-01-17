#include <iostream>
#include "FileMap.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

/**
 * Prints the binary AST to stdout
 * @param root
 */
void printTree(ASTNode* root) {
    if (root == nullptr) {
        return;
    }

    printf("(");
    // If the node is an operator, print the operator
    if (root->dtype == Types::Operator) {

        printf("%s", tokenToName.at(root->type).c_str());
    } else {
        // Otherwise, print the value
        printf("%s", root->toString().c_str());
    }
    printTree(root->left);
    printTree(root->right);

    printf(")");
}


int main() {
    FileMap file("../resources/Sample.b");

    // Tokenize the file
    Scanner scanner(file.begin(), file.end());

    Parser parser(scanner.getTokens());
    struct ASTNode* expr = parser.parse();
    printTree(expr);
    return 0;
}

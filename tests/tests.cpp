//
// Created by Adam Ali on 17/01/2023.
//
#include "gtest/gtest.h"

#include "Token.h"
#include "Lexer.h"
#include "FileMap.h"
#include "Parser.h"

TEST(MathExpressionTest, SampleA) {
    FileMap file("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.b");
    Lexer scanner(file.begin(), file.end());
    printf("Loaded\n");
    while (scanner.hasNext()) {
        Token token = scanner.read();
        printf("%s\n", token.toString().c_str());
    }
}

TEST(ParseTest, PackageDecl) {
    FileMap file("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/PackageDecl.b");
    Lexer scanner(file.begin(), file.end());
    std::vector<Token> tokens;
    while (scanner.hasNext()) {
        tokens.push_back(scanner.read());
    }
    Parser parser(tokens);
    std::vector<ASTNode*> nodes = parser.parse();
    for (ASTNode* node : nodes) {
        printf("%s\n", node->toString().c_str());
    }

    std::vector<ASTNode*> expected = {
            new ASTNode(TokenTypes::TK_PACKAGE, new std::string("main")),
            new ASTNode(TokenTypes::TK_INCLUDE, new std::string("std")),
            new ASTNode(TokenTypes::TK_INCLUDE, new std::string("io")),
    };

    ASSERT_EQ(nodes.size(), expected.size());
    for (int i = 0; i < nodes.size(); i++) {
        ASSERT_EQ(nodes[i]->type, expected[i]->type);
        ASSERT_EQ(*(std::string*) nodes[i]->value, *(std::string*) expected[i]->value);
    }

}

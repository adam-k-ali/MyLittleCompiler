//
// Created by Adam Ali on 17/01/2023.
//
#include "gtest/gtest.h"

#include "Token.h"
#include "Lexer.h"
#include "FileMap.h"

TEST(MathExpressionTest, SampleA) {
    FileMap file("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.b");
    Lexer scanner(file.begin(), file.end());
    printf("Loaded\n");
    while (scanner.hasNext()) {
        Token token = scanner.read();
        printf("%s\n", token.toString().c_str());
    }
}

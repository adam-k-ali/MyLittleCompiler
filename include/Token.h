//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

enum class Token {
    Invalid,
    EndOfFile,

    Number,
    Add,
    Subtract,
    Multiply,
    Divide,
    LeftParen,
    RightParen,
};

// Convert a token to a string
const char* tokenToString(Token token);

#endif //COMPILER_TOKEN_H

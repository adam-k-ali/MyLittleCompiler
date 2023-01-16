//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <string>



enum class TokenType {
    Invalid,
    EndOfFile,

    // Literals
    Number,
    String,
    True,
    False,
    Nil,

    // Operators
    Add,
    Subtract,
    Multiply,
    Divide,
    Minus,

    Bang,
    BangEqual,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,

    // Parenthesis
    LeftParen,
    RightParen,
};

class Token {
private:
    TokenType type;
    char* lexeme;
public:
    Token(TokenType type, char* value) : type(type), lexeme(value) {};
    Token(TokenType type) : type(type), lexeme(nullptr) {};

    TokenType getType() const { return type; }
    char* getLexeme() const { return lexeme; }

    std::string toString() const;
};



#endif //COMPILER_TOKEN_H

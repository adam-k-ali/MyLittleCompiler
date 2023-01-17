//
// Created by Adam Ali on 17/01/2023.
//

#ifndef COMPILER_DEFS_H
#define COMPILER_DEFS_H
#include <map>

#define TEXTLEN     512    // Length of text buffer
extern char Text[TEXTLEN + 1]; // Last identifier scanned

enum class Types {
    Nil,
    Bool,
    Integer,
    Double,
    String,
    Void,
};

enum class TokenType {
    Invalid,
    T_EOF,
    T_SEMICOLON,

    // Literals
    Number,
    Identifier,

    // Keywords
    T_PRINT,
    T_INT,

    // Operators
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_EQUAL,

    // Variable types
    V_INT,
};

// Create map of token types to their string representation
const std::map<TokenType, std::string> TokenToName = {
        {TokenType::Invalid,     "Invalid"},
        {TokenType::T_EOF,       "T_EOF"},
        {TokenType::T_SEMICOLON, "T_SEMICOLON"},

        {TokenType::Number,      "Number"},
        {TokenType::Identifier,  "Identifier"},

        {TokenType::T_PRINT,     "T_PRINT"},
        {TokenType::T_INT,       "T_INT"},

        {TokenType::T_PLUS,      "T_PLUS"},
        {TokenType::T_MINUS,     "T_MINUS"},
        {TokenType::T_STAR, "T_STAR"},
        {TokenType::T_SLASH, "T_SLASH"},
        {TokenType::T_EQUAL, "T_EQUAL"},

        {TokenType::V_INT, "V_INT"},
};

const std::map<std::string, TokenType> NameToKeyword = {
        {"print", TokenType::T_PRINT},
        {"int", TokenType::T_INT},
};

const std::map<TokenType, int> OpPrec = {
        {TokenType::Invalid,     0},
        {TokenType::T_EOF,       0},
        {TokenType::T_SEMICOLON, 0},

        {TokenType::Number,      0},
        {TokenType::Identifier,  0},

        {TokenType::T_PRINT,     0},
        {TokenType::T_INT,       0},

        {TokenType::T_PLUS,      10},
        {TokenType::T_MINUS,     10},
        {TokenType::T_STAR,      20},
        {TokenType::T_SLASH,    20},
        {TokenType::T_EQUAL,    0},
};

struct symtable {
    std::string name;
};

#endif //COMPILER_DEFS_H

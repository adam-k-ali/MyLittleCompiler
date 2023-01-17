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
    Double,
    String,
    Void,
};

enum class TokenType {
    Invalid,
    EndOfFile,
    SemiColon,

    // Literals
    Number,
    Identifier,

    // Keywords
    Print,
    Int,

    // Operators
    Plus,
    Minus,
    Star,
    Slash,
    Assign,
};

// Create map of token types to their string representation
const std::map<TokenType, std::string> TokenToName = {
        {TokenType::Invalid,   "Invalid"},
        {TokenType::EndOfFile, "EndOfFile"},
        {TokenType::SemiColon, "SemiColon"},

        {TokenType::Number,    "Number"},
        {TokenType::Identifier, "Identifier"},

        {TokenType::Print,     "Print"},

        {TokenType::Plus,      "Plus"},
        {TokenType::Minus,     "Minus"},
        {TokenType::Star,      "Star"},
        {TokenType::Slash,     "Slash"},
        {TokenType::Assign,    "Assign"},
};

const std::map<TokenType, int> OpPrec = {
        {TokenType::Invalid,   0},
        {TokenType::EndOfFile, 0},
        {TokenType::SemiColon, 0},

        {TokenType::Number,    0},
        {TokenType::Identifier, 0},

        {TokenType::Print,     0},
        {TokenType::Int,       0},

        {TokenType::Plus,      10},
        {TokenType::Minus,     10},
        {TokenType::Star,      20},
        {TokenType::Slash,     20},
        {TokenType::Assign,    0},
};

struct symtable {
    std::string name;
};

#endif //COMPILER_DEFS_H

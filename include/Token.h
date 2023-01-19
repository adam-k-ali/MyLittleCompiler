//
// Created by Adam Ali on 18/01/2023.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <map>

enum class TokenTypes {
    T_EOF,

    TS_PLUS, // +
    TS_MINUS, // -
    TS_STAR, // *
    TS_SLASH, // /
    TS_MODULO, // %
    TS_EQUALS, // =
    TS_BANG, // !
    TS_AMPERSAND, // &
    TS_PIPE, // |
    TS_SEMICOLON, // ;
    TS_COLON, // :
    TS_LESS_THAN, // <
    TS_GREATER_THAN, // >
    TS_COMMA, // ,
    TS_DOT, // .
    TS_OPEN_BRACE, // {
    TS_CLOSE_BRACE, // }
    TS_OPEN_PAREN, // (
    TS_CLOSE_PAREN, // )
    TS_OPEN_BRACKET, // [
    TS_CLOSE_BRACKET, // ]

    T_IDENTIFIER,
    T_INTEGER,
    T_DECIMAL,
    T_STRING,

    TK_PACKAGE,
    TK_INCLUDE,
    TK_CLASS,
    TK_STRUCT,
    TK_ENUM,

    TK_IF,
    TK_ELSE,
    TK_WHILE,
    TK_FOR,
    TK_RETURN,
    TK_INT,
    TK_FLOAT,
    TK_BOOL,
    TK_STRING,
    TK_CHAR,
    TK_VOID,

    TK_PUBLIC,
    TK_PRIVATE,
    TK_PROTECTED,

    TK_FINAL,
    TK_STATIC,
    TK_CONST,

    TK_NEW,
    TK_ABSTRACT,
    TK_VIRTUAL,
    TK_DELETE,
    TK_TRUE,
    TK_FALSE,


};

static std::map<TokenTypes, std::string> TokenToString = {
        {TokenTypes::T_EOF,            "EOF"},
        {TokenTypes::TS_PLUS,          "TS_PLUS"},
        {TokenTypes::TS_MINUS,         "TS_MINUS"},
        {TokenTypes::TS_STAR,          "TS_STAR"},
        {TokenTypes::TS_SLASH,         "TS_SLASH"},
        {TokenTypes::TS_MODULO,        "TS_MODULO"},
        {TokenTypes::TS_EQUALS,        "TS_EQUALS"},
        {TokenTypes::TS_BANG,          "TS_BANG"},
        {TokenTypes::TS_AMPERSAND,     "TS_AMPERSAND"},
        {TokenTypes::TS_PIPE,          "TS_PIPE"},
        {TokenTypes::TS_SEMICOLON,     "TS_SEMICOLON"},
        {TokenTypes::TS_COLON,         "TS_COLON"},
        {TokenTypes::TS_LESS_THAN,     "TS_LESS_THAN"},
        {TokenTypes::TS_GREATER_THAN,  "TS_GREATER_THAN"},
        {TokenTypes::TS_COMMA,         "TS_COMMA"},
        {TokenTypes::TS_DOT,           "TS_DOT"},
        {TokenTypes::T_IDENTIFIER,     "T_IDENTIFIER"},
        {TokenTypes::T_INTEGER,        "T_INTEGER"},
        {TokenTypes::T_DECIMAL,        "T_DECIMAL"},
        {TokenTypes::T_STRING,         "T_STRING"},
        {TokenTypes::TK_PACKAGE,       "TK_PACKAGE"},
        {TokenTypes::TK_INCLUDE,       "TK_INCLUDE"},
        {TokenTypes::TK_CLASS,         "TK_CLASS"},
        {TokenTypes::TK_IF,            "TK_IF"},
        {TokenTypes::TK_ELSE,          "TK_ELSE"},
        {TokenTypes::TK_WHILE,         "TK_WHILE"},
        {TokenTypes::TK_FOR,           "TK_FOR"},
        {TokenTypes::TK_RETURN,        "TK_RETURN"},
        {TokenTypes::TK_PUBLIC,        "TK_PUBLIC"},
        {TokenTypes::TK_PRIVATE,       "TK_PRIVATE"},
        {TokenTypes::TK_PROTECTED,     "TK_PROTECTED"},
        {TokenTypes::TK_FINAL,         "TK_FINAL"},
        {TokenTypes::TK_STATIC,        "TK_STATIC"},
        {TokenTypes::TK_CONST,         "T_CONST"},
        {TokenTypes::TK_NEW,           "TK_NEW"},
        {TokenTypes::TK_ABSTRACT,      "TK_ABSTRACT"},
        {TokenTypes::TK_VIRTUAL,       "TK_VIRTUAL"},
        {TokenTypes::TK_DELETE,        "TK_DELETE"},
        {TokenTypes::TK_TRUE,          "TK_TRUE"},
        {TokenTypes::TK_FALSE,         "TK_FALSE"},
        {TokenTypes::TS_OPEN_BRACE,    "TS_OPEN_BRACE"},
        {TokenTypes::TS_CLOSE_BRACE,   "TS_CLOSE_BRACE"},
        {TokenTypes::TS_OPEN_PAREN,    "TS_OPEN_PAREN"},
        {TokenTypes::TS_CLOSE_PAREN,   "TS_CLOSE_PAREN"},
        {TokenTypes::TS_OPEN_BRACKET,  "TS_OPEN_BRACKET"},
        {TokenTypes::TS_CLOSE_BRACKET, "TS_CLOSE_BRACKET"},
        {TokenTypes::TK_INT,           "TK_INT"},
        {TokenTypes::TK_FLOAT,         "TK_FLOAT"},
        {TokenTypes::TK_STRUCT,        "TK_STRUCT"},
        {TokenTypes::TK_ENUM,          "TK_ENUM"},
        {TokenTypes::TK_BOOL,          "TK_BOOL"},
        {TokenTypes::TK_STRING,        "TK_STRING"},
        {TokenTypes::TK_CHAR,          "TK_CHAR"},
        {TokenTypes::TK_VOID,          "TK_VOID"},

};

// A map of token names to their corresponding keyword token type
static std::map<std::string, TokenTypes> NameToKeyword = {
        {"package",   TokenTypes::TK_PACKAGE},
        {"include",   TokenTypes::TK_INCLUDE},
        {"class",     TokenTypes::TK_CLASS},
        {"if",        TokenTypes::TK_IF},
        {"else",      TokenTypes::TK_ELSE},
        {"while",     TokenTypes::TK_WHILE},
        {"for",       TokenTypes::TK_FOR},
        {"return",    TokenTypes::TK_RETURN},
        {"public",    TokenTypes::TK_PUBLIC},
        {"private",   TokenTypes::TK_PRIVATE},
        {"protected", TokenTypes::TK_PROTECTED},
        {"final",     TokenTypes::TK_FINAL},
        {"static",    TokenTypes::TK_STATIC},
        {"const",     TokenTypes::TK_CONST},
        {"new",       TokenTypes::TK_NEW},
        {"abstract",  TokenTypes::TK_ABSTRACT},
        {"virtual",   TokenTypes::TK_VIRTUAL},
        {"delete",    TokenTypes::TK_DELETE},
        {"true",      TokenTypes::TK_TRUE},
        {"false",     TokenTypes::TK_FALSE},
        {"int",       TokenTypes::TK_INT},
        {"float",     TokenTypes::TK_FLOAT},
        {"struct",    TokenTypes::TK_STRUCT},
        {"enum",      TokenTypes::TK_ENUM},
        {"bool",      TokenTypes::TK_BOOL},
        {"string",    TokenTypes::TK_STRING},
        {"char",      TokenTypes::TK_CHAR},
        {"void",      TokenTypes::TK_VOID},
};

// A map of token types to their corresponding token name
static std::map<char, TokenTypes> SymbolToToken{
        {'+', TokenTypes::TS_PLUS},
        {'-', TokenTypes::TS_MINUS},
        {'*', TokenTypes::TS_STAR},
        {'/', TokenTypes::TS_SLASH},
        {'%', TokenTypes::TS_MODULO},
        {'=', TokenTypes::TS_EQUALS},
        {'!', TokenTypes::TS_BANG},
        {'&', TokenTypes::TS_AMPERSAND},
        {'|', TokenTypes::TS_PIPE},
        {';', TokenTypes::TS_SEMICOLON},
        {':', TokenTypes::TS_COLON},
        {'<', TokenTypes::TS_LESS_THAN},
        {'>', TokenTypes::TS_GREATER_THAN},
        {',', TokenTypes::TS_COMMA},
        {'.', TokenTypes::TS_DOT},
        {'{', TokenTypes::TS_OPEN_BRACE},
        {'}', TokenTypes::TS_CLOSE_BRACE},
        {'(', TokenTypes::TS_OPEN_PAREN},
        {')', TokenTypes::TS_CLOSE_PAREN},
        {'[', TokenTypes::TS_OPEN_BRACKET},
        {']', TokenTypes::TS_CLOSE_BRACKET},
};

class Token {
private:
    TokenTypes type;
    int line;
    int column;

    std::string *value;
public:
    Token(TokenTypes type, int line, int column) : type(type), line(line), column(column), value(nullptr) {}

    Token(TokenTypes type, std::string *value, int line, int column) : type(type), line(line), column(column),
                                                                       value(value) {}

    TokenTypes getType() const {
        return type;
    }

    int getLine() const {
        return line;
    }

    int getColumn() const {
        return column;
    }

    std::string toString() const {
        // Look up the token type in the map
        std::string tokenName = TokenToString.at(type);

        return tokenName + "[" + std::to_string(line) + ":" + std::to_string(column) + "/" +
               (value != nullptr ? *value : "") + "]";
    }
};


#endif //COMPILER_TOKEN_H

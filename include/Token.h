//
// Created by Adam Ali on 18/01/2023.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <map>

enum class TokenTypes {
    T_EOF,

    T_PLUS, // +
    T_MINUS, // -
    T_STAR, // *
    T_SLASH, // /
    T_MODULO, // %
    T_EQUALS, // =
    T_BANG, // !
    T_AMPERSAND, // &
    T_PIPE, // |
    T_SEMICOLON, // ;
    T_COLON, // :
    T_LESS_THAN, // <
    T_GREATER_THAN, // >
    T_COMMA, // ,
    T_DOT, // .

    T_IDENTIFIER,
    T_INTEGER,
    T_DECIMAL,
    T_STRING,

    T_PACKAGE,
    T_INCLUDE,
    T_CLASS,

    T_IF,
    T_ELSE,
    T_WHILE,
    T_FOR,
    T_RETURN,
    TK_INT,
    TK_FLOAT,

    T_PUBLIC,
    T_PRIVATE,
    T_PROTECTED,

    T_FINAL,
    T_STATIC,
    T_CONST,
    T_NEW,
    T_ABSTRACT,
    T_VIRTUAL,
    T_DELETE,
    T_TRUE,
    T_FALSE,

    T_OPEN_BRACE, // {
    T_CLOSE_BRACE, // }
    T_OPEN_PAREN, // (
    T_CLOSE_PAREN, // )
    T_OPEN_BRACKET, // [
    T_CLOSE_BRACKET, // ]
};

static std::map<TokenTypes, std::string> TokenToString = {
        {TokenTypes::T_EOF, "EOF"},
        {TokenTypes::T_PLUS, "T_PLUS"},
        {TokenTypes::T_MINUS, "T_MINUS"},
        {TokenTypes::T_STAR, "T_STAR"},
        {TokenTypes::T_SLASH, "T_SLASH"},
        {TokenTypes::T_MODULO, "T_MODULO"},
        {TokenTypes::T_EQUALS, "T_EQUALS"},
        {TokenTypes::T_BANG, "T_BANG"},
        {TokenTypes::T_AMPERSAND, "T_AMPERSAND"},
        {TokenTypes::T_PIPE, "T_PIPE"},
        {TokenTypes::T_SEMICOLON, "T_SEMICOLON"},
        {TokenTypes::T_COLON, "T_COLON"},
        {TokenTypes::T_LESS_THAN, "T_LESS_THAN"},
        {TokenTypes::T_GREATER_THAN, "T_GREATER_THAN"},
        {TokenTypes::T_COMMA, "T_COMMA"},
        {TokenTypes::T_DOT, "T_DOT"},
        {TokenTypes::T_IDENTIFIER, "T_IDENTIFIER"},
        {TokenTypes::T_INTEGER, "T_INTEGER"},
        {TokenTypes::T_DECIMAL, "T_DECIMAL"},
        {TokenTypes::T_STRING, "T_STRING"},
        {TokenTypes::T_PACKAGE, "T_PACKAGE"},
        {TokenTypes::T_INCLUDE, "T_INCLUDE"},
        {TokenTypes::T_CLASS, "T_CLASS"},
        {TokenTypes::T_IF, "T_IF"},
        {TokenTypes::T_ELSE, "T_ELSE"},
        {TokenTypes::T_WHILE, "T_WHILE"},
        {TokenTypes::T_FOR, "T_FOR"},
        {TokenTypes::T_RETURN, "T_RETURN"},
        {TokenTypes::T_PUBLIC, "T_PUBLIC"},
        {TokenTypes::T_PRIVATE, "T_PRIVATE"},
        {TokenTypes::T_PROTECTED, "T_PROTECTED"},
        {TokenTypes::T_FINAL, "T_FINAL"},
        {TokenTypes::T_STATIC, "T_STATIC"},
        {TokenTypes::T_CONST, "T_CONST"},
        {TokenTypes::T_NEW, "T_NEW"},
        {TokenTypes::T_ABSTRACT, "T_ABSTRACT"},
        {TokenTypes::T_VIRTUAL, "T_VIRTUAL"},
        {TokenTypes::T_DELETE, "T_DELETE"},
        {TokenTypes::T_TRUE, "T_TRUE"},
        {TokenTypes::T_FALSE, "T_FALSE"},
        {TokenTypes::T_OPEN_BRACE, "T_OPEN_BRACE"},
        {TokenTypes::T_CLOSE_BRACE, "T_CLOSE_BRACE"},
        {TokenTypes::T_OPEN_PAREN, "T_OPEN_PAREN"},
        {TokenTypes::T_CLOSE_PAREN, "T_CLOSE_PAREN"},
        {TokenTypes::T_OPEN_BRACKET, "T_OPEN_BRACKET"},
        {TokenTypes::T_CLOSE_BRACKET, "T_CLOSE_BRACKET"},
        {TokenTypes::TK_INT, "TK_INT"},
        {TokenTypes::TK_FLOAT, "TK_FLOAT"},

};

// A map of token names to their corresponding keyword token type
static std::map<std::string, TokenTypes> NameToKeyword = {
        {"package", TokenTypes::T_PACKAGE},
        {"include", TokenTypes::T_INCLUDE},
        {"class", TokenTypes::T_CLASS},
        {"if", TokenTypes::T_IF},
        {"else", TokenTypes::T_ELSE},
        {"while", TokenTypes::T_WHILE},
        {"for", TokenTypes::T_FOR},
        {"return", TokenTypes::T_RETURN},
        {"public", TokenTypes::T_PUBLIC},
        {"private", TokenTypes::T_PRIVATE},
        {"protected", TokenTypes::T_PROTECTED},
        {"final", TokenTypes::T_FINAL},
        {"static", TokenTypes::T_STATIC},
        {"const", TokenTypes::T_CONST},
        {"new", TokenTypes::T_NEW},
        {"abstract", TokenTypes::T_ABSTRACT},
        {"virtual", TokenTypes::T_VIRTUAL},
        {"delete", TokenTypes::T_DELETE},
        {"true", TokenTypes::T_TRUE},
        {"false", TokenTypes::T_FALSE},
        {"int", TokenTypes::TK_INT},
        {"float", TokenTypes::TK_FLOAT},
};

// A map of token types to their corresponding token name
static std::map<char, TokenTypes> SymbolToToken {
        {'+', TokenTypes::T_PLUS},
        {'-', TokenTypes::T_MINUS},
        {'*', TokenTypes::T_STAR},
        {'/', TokenTypes::T_SLASH},
        {'%', TokenTypes::T_MODULO},
        {'=', TokenTypes::T_EQUALS},
        {'!', TokenTypes::T_BANG},
        {'&', TokenTypes::T_AMPERSAND},
        {'|', TokenTypes::T_PIPE},
        {';', TokenTypes::T_SEMICOLON},
        {':', TokenTypes::T_COLON},
        {'<', TokenTypes::T_LESS_THAN},
        {'>', TokenTypes::T_GREATER_THAN},
        {',', TokenTypes::T_COMMA},
        {'.', TokenTypes::T_DOT},
        {'{', TokenTypes::T_OPEN_BRACE},
        {'}', TokenTypes::T_CLOSE_BRACE},
        {'(', TokenTypes::T_OPEN_PAREN},
        {')', TokenTypes::T_CLOSE_PAREN},
        {'[', TokenTypes::T_OPEN_BRACKET},
        {']', TokenTypes::T_CLOSE_BRACKET},
};

class Token {
private:
    TokenTypes type;
    int line;
    int column;

    std::string* value;
public:
    Token(TokenTypes type, int line, int column) : type(type), line(line), column(column), value(nullptr) {}
    Token(TokenTypes type, std::string* value, int line, int column) : type(type), line(line), column(column), value(value) {}

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

        return tokenName + "[" + std::to_string(line) + ":" + std::to_string(column) + "/" + (value != nullptr ? *value : "") + "]";
    }
};


#endif //COMPILER_TOKEN_H

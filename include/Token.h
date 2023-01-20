//
// Created by Adam Ali on 18/01/2023.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <string>
#include <map>

/**
 * The type of a token
 * Starts with TS_ for a symbol
 * Starts with TK_ for a keyword
 * Starts with TL_ for a literal
 */
enum class TokenTypes {
    T_EOF,
    T_INVALID,

    // Keywords
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

    // Literals
    TL_IDENTIFIER,
    TL_INTEGER,
    TL_DECIMAL,
    TL_STRING,

    // Arithmetic
    TS_PLUS, // +
    TS_MINUS, // -
    TS_STAR, // *
    TS_SLASH, // /
    TS_MODULO, // %
    TS_EQUALS, // =
    TS_PLUS_EQUALS, // +=
    TS_MINUS_EQUALS, // -=
    TS_STAR_EQUALS, // *=
    TS_SLASH_EQUALS, // /=
    TS_MODULO_EQUALS, // %=
    TS_PLUS_PLUS, // ++
    TS_MINUS_MINUS, // --

    // Logical/Comparison
    TS_BANG, // !
    TS_QUESTION_MARK, // ?
    TS_COLON, // :
    TS_GREATER_THAN, // >
    TS_GREATER_THAN_EQUALS, // >=
    TS_LESS_THAN, // <
    TS_LESS_THAN_EQUALS, // <=
    TS_EQUALS_EQUALS, // ==
    TS_BANG_EQUALS, // !=
    TS_AMPERSAND_AMPERSAND, // &&
    TS_PIPE_PIPE, // ||

    // Bitwise Operators
    TS_AMPERSAND, // &
    TS_PIPE, // |
    TS_CARET, // ^
    TS_TILDE, // ~
    TS_AMPERSAND_EQUALS, // &=
    TS_PIPE_EQUALS, // |=
    TS_CARET_EQUALS, // ^=
    TS_TILDE_EQUALS, // ~=
    TS_LEFT_SHIFT, // <<
    TS_RIGHT_SHIFT, // >>
    TS_LEFT_SHIFT_EQUALS, // <<=
    TS_RIGHT_SHIFT_EQUALS, // >>=

    // Structural
    TS_SEMICOLON, // ;
    TS_COMMA, // ,
    TS_DOT, // .
    TS_OPEN_BRACE, // {
    TS_CLOSE_BRACE, // }
    TS_OPEN_PAREN, // (
    TS_CLOSE_PAREN, // )
    TS_OPEN_BRACKET, // [
    TS_CLOSE_BRACKET, // ]
    TS_ARROW, // ->
    TS_DOUBLE_COLON, // ::
    TS_ELLIPSIS, // ...

};

static std::map<TokenTypes, std::string> TokenToString = {
        {TokenTypes::T_EOF,            "T_EOF"},
        {TokenTypes::T_INVALID,        "T_INVALID"},

        // Keywords
        {TokenTypes::TK_PACKAGE,       "TK_PACKAGE"},
        {TokenTypes::TK_INCLUDE,       "TK_INCLUDE"},
        {TokenTypes::TK_CLASS,         "TK_CLASS"},
        {TokenTypes::TK_STRUCT,        "TK_STRUCT"},
        {TokenTypes::TK_ENUM,          "TK_ENUM"},

        {TokenTypes::TK_IF,            "TK_IF"},
        {TokenTypes::TK_ELSE,          "TK_ELSE"},

        {TokenTypes::TK_WHILE,         "TK_WHILE"},
        {TokenTypes::TK_FOR,           "TK_FOR"},

        {TokenTypes::TK_RETURN,        "TK_RETURN"},

        {TokenTypes::TK_INT,           "TK_INT"},
        {TokenTypes::TK_FLOAT,         "TK_FLOAT"},
        {TokenTypes::TK_BOOL,          "TK_BOOL"},
        {TokenTypes::TK_STRING,        "TK_STRING"},
        {TokenTypes::TK_CHAR,          "TK_CHAR"},
        {TokenTypes::TK_VOID,          "TK_VOID"},

        {TokenTypes::TK_PUBLIC,        "TK_PUBLIC"},
        {TokenTypes::TK_PRIVATE,       "TK_PRIVATE"},
        {TokenTypes::TK_PROTECTED,     "TK_PROTECTED"},

        {TokenTypes::TK_FINAL,         "TK_FINAL"},
        {TokenTypes::TK_STATIC,        "TK_STATIC"},
        {TokenTypes::TK_CONST,         "TK_CONST"},

        {TokenTypes::TK_NEW,           "TK_NEW"},
        {TokenTypes::TK_ABSTRACT,      "TK_ABSTRACT"},
        {TokenTypes::TK_VIRTUAL,       "TK_VIRTUAL"},
        {TokenTypes::TK_DELETE,        "TK_DELETE"},

        {TokenTypes::TK_TRUE,          "TK_TRUE"},
        {TokenTypes::TK_FALSE,         "TK_FALSE"},

        // Literals
        {TokenTypes::TL_IDENTIFIER,    "TL_IDENTIFIER"},
        {TokenTypes::TL_INTEGER,       "TL_INTEGER"},
        {TokenTypes::TL_DECIMAL,       "TL_DECIMAL"},
        {TokenTypes::TL_STRING,        "TL_STRING"},

        // Arithmetic
        {TokenTypes::TS_PLUS,          "TS_PLUS"},
        {TokenTypes::TS_MINUS,         "TS_MINUS"},
        {TokenTypes::TS_STAR,          "TS_STAR"},
        {TokenTypes::TS_SLASH,         "TS_SLASH"},
        {TokenTypes::TS_MODULO,        "TS_MODULO"},
        {TokenTypes::TS_EQUALS,        "TS_EQUALS"},
        {TokenTypes::TS_PLUS_EQUALS,   "TS_PLUS_EQUALS"},
        {TokenTypes::TS_MINUS_EQUALS,  "TS_MINUS_EQUALS"},
        {TokenTypes::TS_STAR_EQUALS,   "TS_STAR_EQUALS"},
        {TokenTypes::TS_SLASH_EQUALS,  "TS_SLASH_EQUALS"},
        {TokenTypes::TS_MODULO_EQUALS, "TS_MODULO_EQUALS"},
        {TokenTypes::TS_PLUS_PLUS,     "TS_PLUS_PLUS"},
        {TokenTypes::TS_MINUS_MINUS,   "TS_MINUS_MINUS"},

        // Logical
        {TokenTypes::TS_BANG,          "TS_BANG"},
        {TokenTypes::TS_QUESTION_MARK, "TS_QUESTION_MARK"},
        {TokenTypes::TS_COLON,         "TS_COLON"},
        {TokenTypes::TS_GREATER_THAN,  "TS_GREATER_THAN"},
        {TokenTypes::TS_GREATER_THAN_EQUALS, "TS_GREATER_THAN_EQUALS"},
        {TokenTypes::TS_LESS_THAN,     "TS_LESS_THAN"},
        {TokenTypes::TS_LESS_THAN_EQUALS,    "TS_LESS_THAN_EQUALS"},
        {TokenTypes::TS_EQUALS_EQUALS, "TS_EQUALS_EQUALS"},
        {TokenTypes::TS_BANG_EQUALS,   "TS_BANG_EQUALS"},
        {TokenTypes::TS_AMPERSAND_AMPERSAND, "TS_AMPERSAND_AMPERSAND"},
        {TokenTypes::TS_PIPE_PIPE,     "TS_PIPE_PIPE"},

        // Bitwise
        {TokenTypes::TS_AMPERSAND,     "TS_AMPERSAND"},
        {TokenTypes::TS_PIPE,          "TS_PIPE"},
        {TokenTypes::TS_CARET,         "TS_CARET"},
        {TokenTypes::TS_TILDE,         "TS_TILDE"},
        {TokenTypes::TS_AMPERSAND_EQUALS, "TS_AMPERSAND_EQUALS"},
        {TokenTypes::TS_PIPE_EQUALS,   "TS_PIPE_EQUALS"},
        {TokenTypes::TS_CARET_EQUALS,  "TS_CARET_EQUALS"},
        {TokenTypes::TS_TILDE_EQUALS,  "TS_TILDE_EQUALS"},
        {TokenTypes::TS_LEFT_SHIFT,    "TS_LEFT_SHIFT"},
        {TokenTypes::TS_RIGHT_SHIFT,   "TS_RIGHT_SHIFT"},
        {TokenTypes::TS_LEFT_SHIFT_EQUALS, "TS_LEFT_SHIFT_EQUALS"},
        {TokenTypes::TS_RIGHT_SHIFT_EQUALS, "TS_RIGHT_SHIFT_EQUALS"},

        // Structural
        {TokenTypes::TS_SEMICOLON, "TS_SEMICOLON"},
        {TokenTypes::TS_COMMA,     "TS_COMMA"},
        {TokenTypes::TS_DOT,       "TS_DOT"},
        {TokenTypes::TS_OPEN_BRACE, "TS_OPEN_BRACE"},
        {TokenTypes::TS_CLOSE_BRACE, "TS_CLOSE_BRACE"},
        {TokenTypes::TS_OPEN_PAREN, "TS_OPEN_PAREN"},
        {TokenTypes::TS_CLOSE_PAREN, "TS_CLOSE_PAREN"},
        {TokenTypes::TS_OPEN_BRACKET, "TS_OPEN_BRACKET"},
        {TokenTypes::TS_CLOSE_BRACKET, "TS_CLOSE_BRACKET"},
        {TokenTypes::TS_ARROW, "TS_ARROW"},
        {TokenTypes::TS_DOUBLE_COLON, "TS_DOUBLE_COLON"},
        {TokenTypes::TS_ELLIPSIS, "TS_ELLIPSIS"},
};

// A map of token names to their corresponding keyword token type
static std::map<std::string, TokenTypes> NameToKeyword = {
        {"package",   TokenTypes::TK_PACKAGE},
        {"include",   TokenTypes::TK_INCLUDE},
        {"class",     TokenTypes::TK_CLASS},
        {"struct",    TokenTypes::TK_STRUCT},
        {"enum",      TokenTypes::TK_ENUM},

        {"if",        TokenTypes::TK_IF},
        {"else",      TokenTypes::TK_ELSE},

        {"while",     TokenTypes::TK_WHILE},
        {"for",       TokenTypes::TK_FOR},

        {"return",    TokenTypes::TK_RETURN},

        {"int",       TokenTypes::TK_INT},
        {"float",     TokenTypes::TK_FLOAT},
        {"bool",      TokenTypes::TK_BOOL},
        {"string",    TokenTypes::TK_STRING},
        {"char",      TokenTypes::TK_CHAR},
        {"void",      TokenTypes::TK_VOID},

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
};

// A map of token types to their corresponding token name
static std::map<std::string, TokenTypes> SymbolToToken{
        // Arithmetic
        {"+", TokenTypes::TS_PLUS},
        {"-", TokenTypes::TS_MINUS},
        {"*", TokenTypes::TS_STAR},
        {"/", TokenTypes::TS_SLASH},
        {"%", TokenTypes::TS_MODULO},
        {"=", TokenTypes::TS_EQUALS},
        {"+=", TokenTypes::TS_PLUS_EQUALS},
        {"-=", TokenTypes::TS_MINUS_EQUALS},
        {"*=", TokenTypes::TS_STAR_EQUALS},
        {"/=", TokenTypes::TS_SLASH_EQUALS},
        {"%=", TokenTypes::TS_MODULO_EQUALS},
        {"++", TokenTypes::TS_PLUS_PLUS},
        {"--", TokenTypes::TS_MINUS_MINUS},

        // Logical/Comparison
        {"!", TokenTypes::TS_BANG},
        {"?", TokenTypes::TS_QUESTION_MARK},
        {":", TokenTypes::TS_COLON},
        {">", TokenTypes::TS_GREATER_THAN},
        {">=", TokenTypes::TS_GREATER_THAN_EQUALS},
        {"<", TokenTypes::TS_LESS_THAN},
        {"<=", TokenTypes::TS_LESS_THAN_EQUALS},
        {"==", TokenTypes::TS_EQUALS_EQUALS},
        {"!=", TokenTypes::TS_BANG_EQUALS},
        {"&&", TokenTypes::TS_AMPERSAND_AMPERSAND},
        {"||", TokenTypes::TS_PIPE_PIPE},

        // Bitwise Operators
        {"&", TokenTypes::TS_AMPERSAND},
        {"|", TokenTypes::TS_PIPE},
        {"^", TokenTypes::TS_CARET},
        {"~", TokenTypes::TS_TILDE},
        {"&=", TokenTypes::TS_AMPERSAND_EQUALS},
        {"|=", TokenTypes::TS_PIPE_EQUALS},
        {"^=", TokenTypes::TS_CARET_EQUALS},
        {"~=", TokenTypes::TS_TILDE_EQUALS},
        {"<<", TokenTypes::TS_LEFT_SHIFT},
        {">>", TokenTypes::TS_RIGHT_SHIFT},
        {"<<=", TokenTypes::TS_LEFT_SHIFT_EQUALS},
        {">>=", TokenTypes::TS_RIGHT_SHIFT_EQUALS},

        // Structural
        {";", TokenTypes::TS_SEMICOLON},
        {",", TokenTypes::TS_COMMA},
        {".", TokenTypes::TS_DOT},
        {"{", TokenTypes::TS_OPEN_BRACE},
        {"}", TokenTypes::TS_CLOSE_BRACE},
        {"(", TokenTypes::TS_OPEN_PAREN},
        {")", TokenTypes::TS_CLOSE_PAREN},
        {"[", TokenTypes::TS_OPEN_BRACKET},
        {"]", TokenTypes::TS_CLOSE_BRACKET},
        {"->", TokenTypes::TS_ARROW},
        {"::", TokenTypes::TS_DOUBLE_COLON},
        {"...", TokenTypes::TS_ELLIPSIS},
};

// Operator Precedence
static std::map<TokenTypes, int> OpPrec = {
        {TokenTypes::TS_PLUS, 10},
        {TokenTypes::TS_MINUS, 10},
        {TokenTypes::TS_STAR, 20},
        {TokenTypes::TS_SLASH, 20},
        {TokenTypes::TS_MODULO, 20},
        {TokenTypes::TS_EQUALS, 30},
        {TokenTypes::TS_PLUS_EQUALS, 30},
        {TokenTypes::TS_MINUS_EQUALS, 30},
        {TokenTypes::TS_STAR_EQUALS, 30},
        {TokenTypes::TS_SLASH_EQUALS, 30},
        {TokenTypes::TS_MODULO_EQUALS, 30},
        {TokenTypes::TS_PLUS_PLUS, 30},
        {TokenTypes::TS_MINUS_MINUS, 30},
        {TokenTypes::TS_BANG, 40},
        {TokenTypes::TS_QUESTION_MARK, 50},
        {TokenTypes::TS_COLON, 50},
        {TokenTypes::TS_GREATER_THAN, 60},
        {TokenTypes::TS_GREATER_THAN_EQUALS, 60},
        {TokenTypes::TS_LESS_THAN, 60},
        {TokenTypes::TS_LESS_THAN_EQUALS, 60},
        {TokenTypes::TS_EQUALS_EQUALS, 70},
        {TokenTypes::TS_BANG_EQUALS, 70},
        {TokenTypes::TS_AMPERSAND_AMPERSAND, 80},
        {TokenTypes::TS_PIPE_PIPE, 90},
        {TokenTypes::TS_AMPERSAND, 100},
        {TokenTypes::TS_PIPE, 110},
        {TokenTypes::TS_CARET, 120},
        {TokenTypes::TS_TILDE, 130},
        {TokenTypes::TS_AMPERSAND_EQUALS, 140},
        {TokenTypes::TS_PIPE_EQUALS, 150},
        {TokenTypes::TS_CARET_EQUALS, 160},
        {TokenTypes::TS_TILDE_EQUALS, 170},
        {TokenTypes::TS_LEFT_SHIFT, 180},
        {TokenTypes::TS_RIGHT_SHIFT, 180},
        {TokenTypes::TS_LEFT_SHIFT_EQUALS, 190},
        {TokenTypes::TS_RIGHT_SHIFT_EQUALS, 190},
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

    std::string *getValue() const {
        return value;
    }

    std::string toString() const {
        // Look up the token type in the map
        std::string tokenName = TokenToString.at(type);

        return tokenName + "[" + std::to_string(line) + ":" + std::to_string(column) + "/" +
               (value != nullptr ? *value : "") + "]";
    }
};


#endif //COMPILER_TOKEN_H

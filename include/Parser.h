//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <utility>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Expr.h"

class ParseError : public std::exception {
private:
    Token token;
    std::string message;
public:
    ParseError(const Token& token, std::string message) : token(token), message(std::move(message)) {};

    const char *what() const noexcept override {
        return message.c_str();
    }
};


class Parser {
private:
    const std::vector<Token> tokens;

    size_t current = 0;

    Token previous();
    Token peek();
    Token next();

    Token advance();
    Token consume(TokenType type, std::string message);

    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type);
    bool isAtEnd();

    Expr* parseEquality();
    Expr* parseComparison();
    Expr* parseTerm();
    Expr* parseFactor();
    Expr* parseUnary();
    Expr* parsePrimary();

    ParseError error(Token token, std::string message);
public:
    explicit Parser(const std::vector<Token> tokens) : tokens(tokens) {};

    Expr* parse();
};


#endif //COMPILER_PARSER_H

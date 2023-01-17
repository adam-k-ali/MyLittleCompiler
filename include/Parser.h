//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <utility>
#include <list>
#include <vector>
#include "Token.h"
#include "Lexer.h"
#include "defs.h"

class ParseError : public std::exception {
private:
    Token token;
    std::string message;
    int line;
    int column;
public:
    ParseError(const Token &token, std::string message) : token(token) {
        this->line = token.getLine();
        this->column = token.getColumn();
        this->message = "SyntaxError: " + message + " at " + std::to_string(line) + ":" + std::to_string(column);
    };

    const char *what() const noexcept override {
        return message.c_str();
    }
};


class Parser {
private:
    static int getPrecedence(TokenType type) {
        return OpPrec.at(type);
    }

    const std::vector<Token> tokens;

    size_t current = 0;
    size_t column = 0;
    size_t line = 1;

    Token previous();
    Token peek();
    Token next();

    Token advance();
    Token consume(TokenType type, std::string message);

    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type);
    bool isAtEnd();

    /**
     * Parses a unary expression
     * @return The AST node for the primary factor
     */
    struct ASTNode* parseLiteral();

    /**
     * Parses a binary expression
     * @return The AST node for the binary expression
     */
     struct ASTNode* parseBinary();

     /**
      * Parse a statement
      * @return The AST node for the statement
      */
     struct std::list<ASTNode*> parseStatements();

     struct ASTNode* parsePrintStmt();
     struct ASTNode* parseVarDeclStmt();
    struct ASTNode* parseAssignmentStmt();

public:
    explicit Parser(const std::vector<Token> tokens) : tokens(tokens) {};

    struct std::list<ASTNode*> parse();
};


#endif //COMPILER_PARSER_H

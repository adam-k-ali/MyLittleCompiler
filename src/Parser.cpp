//
// Created by Adam Ali on 16/01/2023.
//

#include "Parser.h"

#include <utility>




Token Parser::previous() {
    if (current == 0) {
        return {TokenType::Invalid, 0, 0};
    }
    return tokens[current - 1];
}

Token Parser::peek() {
    if(tokens.size() <= current) {
        return {TokenType::T_EOF, 0, 0};
    }
    return tokens.at(current);
}

Token Parser::next() {
    if (current + 1 >= tokens.size()) {
        return {TokenType::Invalid, 0, 0};
    }
    return tokens.at(current + 1);
}

Token Parser::advance() {
    if (!isAtEnd()) {
        current++;
    }
    return previous();
}

Token Parser::consume(TokenType type, std::string message) {
    if (check(type)) {
        return advance();
    }
    throw ParseError(peek(), message);
//    throw ParseError(peek(), std::move(message), Token(TokenType::T_SLASH, nullptr, 0, 0));
}


bool Parser::match(const std::vector<TokenType>& types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return peek().getType() == type;
}

bool Parser::isAtEnd() {
    if (current >= tokens.size()) {
        return true;
    }
    return peek().getType() == TokenType::T_EOF;
}

struct std::list<ASTNode*> Parser::parse() {
    try {
        if (tokens.empty()) {
            throw ParseError({TokenType::Invalid, 0, 0}, "No tokens to parse");
        }
        return parseStatements();
    } catch (ParseError &error) {
        std::cout << error.what() << std::endl;
        return {};
    }
}

struct ASTNode *Parser::parseBinary() {
    int prevPrec = getPrecedence(previous().getType());

    struct ASTNode *left, *right;

    left = parseLiteral();
    if (isAtEnd()) {
        return left;
    }

    while (getPrecedence(peek().getType()) > prevPrec) {
        Token token = advance();
        right = parseBinary();
        left = new ASTNode(token.getType(), Types::Void, left, right);
        if (isAtEnd() || peek().getType() == TokenType::T_SEMICOLON) {
            return left;
        }
    }
    return left;
}

struct ASTNode *Parser::parseLiteral() {
    // Check if the token is a number
    if (match({TokenType::Number})) {
        return new ASTNode(TokenType::Number, new double(std::stod(previous().getValue())), Types::Integer);
    }
    if (match({TokenType::Identifier})) {
        return new ASTNode(TokenType::Identifier, new std::string(previous().getValue()), Types::String);
    }

    throw ParseError(peek(), "Expected expression");
}

struct std::list<ASTNode*> Parser::parseStatements() {
    std::list<struct ASTNode*> statements;

    while (match({TokenType::T_PRINT, TokenType::T_INT, TokenType::Identifier})) {
        Token token = previous(); // Store the token that's been matched
        switch (token.getType()) {
            case TokenType::T_PRINT:
                statements.push_back(parsePrintStmt());
                break;
            case TokenType::T_INT:
                statements.push_back(parseVarDeclStmt());
                break;
            case TokenType::Identifier:
                statements.push_back(parseAssignmentStmt());
                break;
            default:
                throw ParseError(token, "Expected statement");
        }
    }
    if (statements.empty()) {
        throw ParseError(peek(), "Expected statement");
    }

    return statements;
}


struct ASTNode *Parser::parseVarDeclStmt() {
    ASTNode *left, *right;
    // The next token should be the identifier
    Token identifier = consume(TokenType::Identifier, "Expected identifier after 'int'");
    left = new ASTNode(identifier.getType(), identifier.getValue(), Types::String);

    // The next token should be the assignment operator or a semicolon
    if (match({TokenType::T_EQUAL})) {
        // The next token should be the value
        right = parseBinary();
        consume(TokenType::T_SEMICOLON, "Expected ';' after value");
        return new ASTNode(TokenType::V_INT, Types::Void, left, right);
    } else if (match({TokenType::T_SEMICOLON})) {
        return new ASTNode(TokenType::V_INT, Types::Void, left, nullptr);
    }

    throw ParseError(peek(), "Expected '=' or ';' after identifier");
}

struct ASTNode *Parser::parsePrintStmt() {
    struct ASTNode *root, *left;
    left = parseBinary();
    root = new ASTNode(TokenType::T_PRINT, Types::Void, left, nullptr);
    consume(TokenType::T_SEMICOLON, "Expected ';' after expression");
    return root;
}

struct ASTNode *Parser::parseAssignmentStmt() {
    struct ASTNode *root, *left, *right;
    Token identifier = previous();
    consume(TokenType::T_EQUAL, "Expected '=' after identifier");
    right = parseBinary();
    consume(TokenType::T_SEMICOLON, "Expected ';' after expression");
    left = new ASTNode(identifier.getType(), identifier.getValue(), Types::String);
    root = new ASTNode(TokenType::T_EQUAL, Types::Void, left, right);
    return root;
}
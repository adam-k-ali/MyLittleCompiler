//
// Created by Adam Ali on 16/01/2023.
//

#include "Parser.h"

#include <utility>



Token Parser::previous() {
    if (current == 0) {
        return {TokenType::Invalid};
    }
    return tokens[current - 1];
}

Token Parser::peek() {
    if(tokens.size() <= current) {
        return {TokenType::EndOfFile};
    }
    return tokens.at(current);
}

Token Parser::next() {
    if (current + 1 >= tokens.size()) {
        return {TokenType::Invalid};
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

    throw ParseError(peek(), std::move(message));
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
    return peek().getType() == TokenType::EndOfFile;
}

struct ASTNode* Parser::parse() {
    try {
        if (tokens.empty()) {
            throw ParseError({TokenType::Invalid}, "No tokens to parse");
        }
        return parseStatement();
    } catch (ParseError &error) {
        std::cout << error.what() << std::endl;
        return nullptr;
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
        if (isAtEnd() || peek().getType() == TokenType::SemiColon) {
            return left;
        }
    }
    return left;
}

struct ASTNode *Parser::parseLiteral() {
    // Check if the token is a number
    if (match({TokenType::Number})) {
        return new ASTNode(TokenType::Number, new double(std::stod(previous().getValue())), Types::Double);
    }

    throw ParseError(peek(), "Expected expression");
}

struct ASTNode *Parser::parseStatement() {
    struct ASTNode *root, *left;
    if (match({TokenType::Print, TokenType::Int, TokenType::Identifier})) {
        Token token = previous();
        switch (token.getType()) {
            case TokenType::Print:
                left = parseLiteral();
                break;
            case TokenType::Int:
                left = parseDeclaration();
                break;
            case TokenType::Identifier:
                left = parseAssignment();
                break;
        }
        left = parseBinary();
        root = new ASTNode(TokenType::Print, Types::Void, left, nullptr);
        consume(TokenType::SemiColon, "Expected ';' after expression");
        return root;
    }
}


struct ASTNode *Parser::parseVarDeclStmt() {
    // int foo = 5;
    // The next token should be the identifier
    Token identifier = consume(TokenType::Identifier, "Expected identifier after 'int'");
    // The next token should be the equals sign
    consume(TokenType::Assign, "Expected '=' after identifier");
    // The next token should be the value
    Token value = consume(TokenType::Number, "Expected value after '='");
    // The next token should be the semicolon
    consume(TokenType::SemiColon, "Expected ';' after value");
    ASTNode* identifierNode = new ASTNode(identifier.getType(), identifier.getValue(), Types::String);
    ASTNode* valueNode = new ASTNode(value.getType(), new double(std::stod(value.getValue())), Types::Double);
    return new ASTNode(TokenType::Int, Types::Void, identifierNode, valueNode);
}

struct ASTNode *Parser::parsePrintStmt() {
    struct ASTNode *root, *left;
    left = parseBinary();
    root = new ASTNode(TokenType::Print, Types::Void, left, nullptr);
    consume(TokenType::SemiColon, "Expected ';' after expression");
    return root;
}

struct ASTNode *Parser::parseAssignmentStmt() {
    struct ASTNode *root, *left, *right;
    Token identifier = previous();
    consume(TokenType::Assign, "Expected '=' after identifier");
    left = parseBinary();
    root = new ASTNode(TokenType::Assign, Types::Void, left, nullptr);
    return root;
}
//
// Created by Adam Ali on 16/01/2023.
//

#include "Parser.h"

Token Parser::previous() {
    return tokens[current - 1];
}

Token Parser::peek() {
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

    throw ParseError(peek(), message);
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
        return parseAddition();
    } catch (ParseError &error) {
        std::cout << error.what() << std::endl;
        return nullptr;
    }
}

struct ASTNode *Parser::parseLiteral() {
    // Check if the token is a number
    if (match({TokenType::Number})) {
        return new ASTNode(TokenType::Number, new double(std::stod(previous().getValue())), Types::Double);
    }

    throw ParseError(peek(), "Expected expression");
}

struct ASTNode *Parser::parseAddition() {
    struct ASTNode *left, *right;
    // Get left-subtree as precedence
    left = parseMultiplication();
    // If we're at the end of the expression, return the left node
    if (isAtEnd()) {
        return left;
    }

    // Check if the next token is a binary operator
    while (match({TokenType::Add, TokenType::Minus})) {
        TokenType type = previous().getType();
        // Set the right node as the right child
        right = parseMultiplication();

        left = new ASTNode(type, nullptr, Types::Operator, left, right);

        if (isAtEnd()) {
            break;
        }
    }

    return left;
}

struct ASTNode *Parser::parseMultiplication() {
    struct ASTNode *left, *right;

    left = parseLiteral();
    // If we're at the end of the expression, return the left node
    if (isAtEnd()) {
        return left;
    }

    // Check if the next token is a binary operator
    while (match({TokenType::Star, TokenType::Slash})) {
        TokenType type = previous().getType();

        right = parseLiteral();

        left = new ASTNode(type, nullptr, Types::Operator, left, right);
        if (isAtEnd()) {
            break;
        }
    }

    return left;
}
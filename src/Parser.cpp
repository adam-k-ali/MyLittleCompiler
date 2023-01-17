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
        return parseBinary();
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
//    if (match({TokenType::String})) {
//        return new ASTNode(TokenType::String, previous().getValue(), Types::String);
//    }
//    if (match({TokenType::True})) {
//        return new ASTNode(TokenType::True, previous().getValue(), Types::Bool);
//    }
//    if (match({TokenType::False})) {
//        return new ASTNode(TokenType::False, previous().getValue(), Types::Bool);
//    }

    throw ParseError(peek(), "Expected expression");
}

struct ASTNode *Parser::parseBinary() {
    struct ASTNode* left = parseLiteral();
    // If we're at the end of the expression, return the left node
    if (isAtEnd()) {
        return left;
    }

    // Check if the next token is a binary operator
    if (match({TokenType::Add, TokenType::Minus, TokenType::Star, TokenType::Slash})) {
        // If it is, create a new node with the operator as the type
        auto* node = new ASTNode(previous().getType(), nullptr, Types::Operator);
        // Set the left node as the left child
        node->left = left;
        // Set the right node as the right child
        node->right = parseBinary();
        // Return the node
        return node;
    }
    return nullptr;
}

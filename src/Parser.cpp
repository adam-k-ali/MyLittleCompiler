//
// Created by Adam Ali on 16/01/2023.
//

#include "Parser.h"

std::map<TokenType, int> Parser::OpPrec = {
        {TokenType::Invalid, 0},
        {TokenType::EndOfFile, 0},

        {TokenType::Number, 0},

        {TokenType::Add, 10},
        {TokenType::Minus, 10},
        {TokenType::Star, 20},
        {TokenType::Slash, 20},
};

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
        left = new ASTNode(token.getType(), Types::Operator, left, right);
        if (isAtEnd()) {
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
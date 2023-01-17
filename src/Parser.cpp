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
        left = new ASTNode(token.getType(), Types::Operator, left, right);
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
    if (match({TokenType::Print})) {
        left = parseBinary();
        root = new ASTNode(TokenType::Print, Types::Operator, left, nullptr);
        consume(TokenType::SemiColon, "Expected ';' after expression");
        return root;
    }
}
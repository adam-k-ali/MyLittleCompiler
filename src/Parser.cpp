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

Expr *Parser::parse() {
    try {
        if (tokens.empty()) {
            throw ParseError({TokenType::Invalid}, "No tokens to parse");
        }

        return parseEquality();
    } catch (ParseError &error) {
        std::cout << error.what() << std::endl;
        return nullptr;
    }
}

Expr *Parser::parseEquality() {
    printf("parseEquality\n");
    Expr *expr = parseComparison();

    while(match({TokenType::EqualEqual, TokenType::BangEqual})) {
        Token operatorToken = previous();
        Expr *right = parseComparison();
        expr = new BinaryExpr(expr, operatorToken, right);
    }

    return expr;
}

Expr *Parser::parseComparison() {
    printf("parseComparison\n");
    Expr *expr = parseTerm();

    while (match({TokenType::Greater, TokenType::GreaterEqual, TokenType::Less, TokenType::LessEqual})) {
        Token operatorToken = previous();
        Expr *right = parseTerm();
        expr = new BinaryExpr(expr, operatorToken, right);
    }

    return expr;
}

Expr *Parser::parseTerm() {
    printf("parseTerm\n");
    Expr *expr = parseFactor();

    while (match({TokenType::Add, TokenType::Subtract})) {
        Token operatorToken = previous();
        Expr *right = parseFactor();
        expr = new BinaryExpr(expr, operatorToken, right);
    }

    return expr;
}

Expr *Parser::parseFactor() {
    printf("parseFactor\n");
    Expr* expr = parseUnary();

    while (match({TokenType::Divide, TokenType::Multiply})) {
        Token operatorToken = previous();
        Expr* right = parseUnary();
        expr = new BinaryExpr(expr, operatorToken, right);
    }

    return expr;
}

Expr *Parser::parseUnary() {
    printf("parseUnary\n");
    if (match({TokenType::Bang, TokenType::Minus})) {
        Token operatorToken = previous();
        Expr* right = parseUnary();
        return new UnaryExpr(operatorToken, right);
    }
    return parsePrimary();
}

Expr *Parser::parsePrimary() {
    printf("parsePrimary\n");
    if (match({TokenType::True})) {
        return new LiteralExpr(new bool(true), Constants::Bool);
    }
    if (match({TokenType::False})) {
        return new LiteralExpr(new bool(false), Constants::Bool);
    }
    if (match({TokenType::Nil})) {
        return new LiteralExpr(nullptr, Constants::Nil);
    }

    if (match({TokenType::Number})) {
        return new LiteralExpr(new double(std::stod(previous().getLexeme())), Constants::Double);
    }
    if (match({TokenType::String})) {
        return new LiteralExpr(new std::string(previous().getLexeme()), Constants::String);
    }

    if (match({TokenType::LeftParen})) {
        Expr* expr = parse();
        consume(TokenType::RightParen, "Expected ')' after expression.");
        return new GroupingExpr(expr);
    }

    throw ParseError(peek(), "Expected expression.");
}


//ParseError Parser::error(Token token, std::string message) {
//    if (token.getType() == TokenType::Invalid) {
//        std::cout << "Error at end: " << message << std::endl;
//    } else {
//        std::cout << "Error at " << token.getLexeme() << ": " << message << std::endl;
//    }
//    return ParseError();
//}

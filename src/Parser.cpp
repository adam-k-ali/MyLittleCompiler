//
// Created by Adam Ali on 20/01/2023.
//

#include "Parser.h"

Token Parser::peek() {
    return m_tokens[m_current];
}

Token Parser::previous() {
    if (m_current == 0) {
        return {TokenTypes::T_INVALID, 0, 0};
    }
    return m_tokens[m_current - 1];
}

Token Parser::next() {
    if (m_current >= m_tokens.size()) {
        return {TokenTypes::T_INVALID, 0, 0};
    }
    return m_tokens[m_current + 1];
}

Token Parser::advance() {
    if (m_current >= m_tokens.size()) {
        return {TokenTypes::T_INVALID, 0, 0};
    }
    return m_tokens[m_current++];
}

bool Parser::isAtEnd() {
    return m_current >= m_tokens.size();
}

bool Parser::check(TokenTypes type) {
    if (isAtEnd()) {
        return false;
    }
    return peek().getType() == type;
}

bool Parser::match(std::vector<TokenTypes> types) {
    for (TokenTypes type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

void Parser::consume(TokenTypes type, const std::string &message) {
    if (check(type)) {
        advance();
        return;
    }
    throw ParserError(message, peek().getLine(), peek().getColumn());
}

int Parser::getPrecedence(TokenTypes type) {
    if (OpPrec.find(type) != OpPrec.end()) {
        return OpPrec[type];
    }
    return -1;
}

ASTNode* Parser::literal() {
    if (match({TokenTypes::TL_INTEGER})) {
        return new ASTNode(TokenTypes::TL_INTEGER, new int(std::stoi(*previous().getValue())));
    }
    if (match({TokenTypes::TL_DECIMAL})) {
        return new ASTNode(TokenTypes::TL_DECIMAL, new double(std::stod(*previous().getValue())));
    }
    if (match({TokenTypes::TL_STRING})) {
        return new ASTNode(TokenTypes::TL_STRING, new std::string(*previous().getValue()));
    }

    throw ParserError("Expected literal", peek().getLine(), peek().getColumn());
}

ASTNode* Parser::binary() {
    int previousPrecedence = getPrecedence(previous().getType());

    ASTNode *left, *right;
    left = literal();
    if (isAtEnd()) {
        return left;
    }

    while (getPrecedence(peek().getType()) > previousPrecedence) {
        TokenTypes op = advance().getType();
        right = binary();
        left = new ASTNode(op, nullptr, {left, right});
        if (isAtEnd() || peek().getType() == TokenTypes::TS_SEMICOLON) {
            break;
        }
    }

    return left;
}

ASTNode* Parser::packageDeclaration() {
    consume(TokenTypes::TK_PACKAGE, "Expected 'package' keyword");
    std::string *name = advance().getValue();
    consume(TokenTypes::TS_SEMICOLON, "Expected ';' after package name");
    return new ASTNode(TokenTypes::TK_PACKAGE, name);
}

std::vector<ASTNode*> Parser::includeStatements() {
    std::vector<ASTNode*> includes;
    while (match({TokenTypes::TK_INCLUDE})) {
        std::string *name = advance().getValue();
        consume(TokenTypes::TS_SEMICOLON, "Expected ';' after include name");
        includes.push_back(new ASTNode(TokenTypes::TK_INCLUDE, name));
    }
    return includes;
}

ASTNode* Parser::structureDeclaration() {
    if (match({TokenTypes::TK_CLASS, TokenTypes::TK_STRUCT, TokenTypes::TK_ENUM})) {
        TokenTypes type = previous().getType();
        std::string *name = previous().getValue();
        // Check for inheritance
        if (match({TokenTypes::TS_COLON})) {
            // Until we get to the end of the inheritance list, which is list of identifiers separated by commas.
            // It ends with a TS_OPEN_BRACE

        }
        return new ASTNode(type, name);
    }
}

std::vector<ASTNode*> Parser::parse() {
    std::vector<ASTNode*> nodes;

    // Every file starts with a package declaration
    ASTNode* package = packageDeclaration();
    nodes.push_back(package);

    // Followed by any number of include statements
    std::vector<ASTNode*> includes = includeStatements();
    nodes.insert(nodes.end(), includes.begin(), includes.end());

    return nodes;
}
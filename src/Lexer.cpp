//
// Created by Adam Ali on 16/01/2023.
//

#include <vector>
#include "Lexer.h"

void Lexer::advance() {
    // Move the current pointer to the next character
    m_current++;
    // If the current character is a newline, increment the line counter
    if (*m_current == '\n') {
        line++;
        column = 0;
    } else {
        column++;
    }
}

int Lexer::skip() {
    int count = 0;
    std::vector<char> skipChars = {' ', '\t', '\n', '\r', '\f'};
    while(m_current != m_end) {
        if (std::find(skipChars.begin(), skipChars.end(), *m_current) != skipChars.end()) {
            advance();
            ++count;
        } else {
            break;
        }
    }
    return count;
}

Token Lexer::readNumber() {
    bool digitFlag = false;
    bool decimalFlag = false;

    // Temporary start for the token
    const char* start = m_current;

    std::string value = "";

    // Check if the first character is a digit or a decimal
    while(m_current != m_end) {
        if (*m_current == '.') {
            if (decimalFlag) {
                throw LexerError("Unexpected decimal point", line, column);
            }
            decimalFlag = true;
            value += *m_current;
            advance();
        } else if (isdigit(*m_current)) {
            digitFlag = true;
            value += *m_current;
            advance();
        } else {
            break;
        }
    }

    if (!digitFlag) {
        throw LexerError("Unexpected character", line, column);
    }

    char* c_value = new char[value.length() + 1];
    strcpy(c_value, value.c_str());

    return {TokenType::Number, c_value, line, column};
}

Token Lexer::readIdentifier() {
    std::string value = "";
    while(m_current != m_end) {
        if (!isalnum(*m_current) && *m_current != '_') {
            break;
        }
        value += *m_current;
        advance();
    }
    char* c_value = new char[value.length() + 1];
    strcpy(c_value, value.c_str());
    return {TokenType::Identifier, c_value, line, column};
}

Token Lexer::readKeyword(Token token) {
    int i = 0;
    char* tokenValue = token.getValue();
    if (NameToKeyword.find(tokenValue) != NameToKeyword.end()) {
        TokenType type = NameToKeyword.at(std::string(tokenValue));
        return {type, tokenValue, line, column};
    }
    return {TokenType::Invalid, line, column};
}

Token Lexer::read() {
    // Skip whitespace
    skip();

    // Check if we've reached the end of the file
    if (m_current == m_end) {
        return {TokenType::T_EOF, line, column};
    }

    char c = *m_current;

    switch(c) {
        case EOF:
            return {TokenType::T_EOF, line, column};
        case '+':
            advance();
            return {TokenType::T_PLUS, line, column};
        case '-':
            advance();
            return {TokenType::T_MINUS, line, column};
        case '*':
            advance();
            return {TokenType::T_STAR, line, column};
        case '/':
            advance();
            return {TokenType::T_SLASH, line, column};
        case ';':
            advance();
            return {TokenType::T_SEMICOLON, line, column};
        case '=':
            advance();
            return {TokenType::T_EQUAL, line, column};
        default:
            // Check if the character is a digit, if so, read a number
            if (isdigit(c)) {
                return readNumber();
            }

            // Check if the character is a letter, if so, read an identifier
            if(isalpha(c) || c == '_') {
                Token tok = readIdentifier();
                Token keyword = readKeyword(tok);
                // If the token is a keyword, return the keyword token
                if (keyword.getType() != TokenType::Invalid) {
                    return keyword;
                }
                // Otherwise, the token is an identifier
                return tok;
            }
    }
    return {TokenType::Invalid, line, column};
}

std::vector<Token> Lexer::getTokens() {
    std::vector<Token> tokens;
    Token token = Token(TokenType::Invalid, line, column);

    while ((token = read()).getType() != TokenType::T_EOF && token.getType() != TokenType::Invalid) {
        tokens.push_back(token);
    }

    tokens.push_back({TokenType::T_EOF, line, column});

    return tokens;
}

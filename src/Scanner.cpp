//
// Created by Adam Ali on 16/01/2023.
//

#include <vector>
#include "Scanner.h"

Token Scanner::readNumber() {
    bool digitFlag = false;
    bool decimalFlag = false;

    // Temporary start for the token
    const char* start = m_current;

    std::string value = "";

    // Check if the first character is a digit or a decimal
    while(m_current != m_end) {
        if (*m_current == '.') {
            if (decimalFlag) {
                return {TokenType::Invalid};
            }
            decimalFlag = true;
            value += *m_current;
            ++m_current;
        } else if (isdigit(*m_current)) {
            digitFlag = true;
            value += *m_current;
            ++m_current;
        } else {
            break;
        }
    }

    if (!digitFlag) {
        return {TokenType::Invalid};
    }

    char* c_value = new char[value.length() + 1];
    strcpy(c_value, value.c_str());

    return {TokenType::Number, c_value};
}

Token Scanner::read() {
    // Skip whitespace
    while (m_current != m_end && isspace(*m_current)) {
        ++m_current;
    }

    // Check if we've reached the end of the file
    if (m_current == m_end) {
        return {TokenType::EndOfFile};
    }

    char c = *m_current;

    // Operators
    if ('+' == c) {
        ++m_current;
        return {TokenType::Add};
    }
    if ('-' == c) {
        ++m_current;
        return {TokenType::Minus};
    }
    if ('*' == c) {
        ++m_current;
        return {TokenType::Star};
    }
    if ('/' == c) {
        ++m_current;
        return {TokenType::Slash};
    }
    // Parentheses
    if ('(' == c) {
        ++m_current;
        return {TokenType::LeftParen};
    }
    if (')' == c) {
        ++m_current;
        return {TokenType::RightParen};
    }

    // Check if we're reading a number
    if ('.' == c || isdigit(c)) {
        return readNumber();
    }

    return {TokenType::Invalid};
}

std::vector<Token> Scanner::getTokens() {
    std::vector<Token> tokens;
    Token token = Token(TokenType::Invalid);

    while ((token = read()).getType() != TokenType::EndOfFile && token.getType() != TokenType::Invalid) {
        tokens.push_back(token);
    }

    return tokens;
}

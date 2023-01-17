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

int Scanner::skip() {
    int count = 0;
    std::vector<char> skipChars = {' ', '\t', '\n', '\r', '\f'};
    while(m_current != m_end) {
        if (std::find(skipChars.begin(), skipChars.end(), *m_current) != skipChars.end()) {
            ++m_current;
            ++count;
        } else {
            break;
        }
    }
    return count;
}

Token Scanner::read() {
    // Skip whitespace
    skip();

    // Check if we've reached the end of the file
    if (m_current == m_end) {
        return {TokenType::EndOfFile};
    }

    char c = *m_current;

    switch(c) {
        case EOF:
            return {TokenType::EndOfFile};
        case '+':
            ++m_current;
            return {TokenType::Plus};
        case '-':
            ++m_current;
            return {TokenType::Minus};
        case '*':
            ++m_current;
            return {TokenType::Star};
        case '/':
            ++m_current;
            return {TokenType::Slash};
        default:
            if (isdigit(c)) {
                return readNumber();
            } else {
                return {TokenType::Invalid};
            }
    }
}

std::vector<Token> Scanner::getTokens() {
    std::vector<Token> tokens;
    Token token = Token(TokenType::Invalid);

    while ((token = read()).getType() != TokenType::EndOfFile && token.getType() != TokenType::Invalid) {
        tokens.push_back(token);
    }

    return tokens;
}

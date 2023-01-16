//
// Created by Adam Ali on 16/01/2023.
//

#include "Scanner.h"

Token Scanner::readNumber() {
    bool digitFlag = false;
    bool decimalFlag = false;

    while (m_current != m_end) {
        char c = *m_current;

        if (c == '.') {
            if (decimalFlag) {
                return Token::Invalid;
            }
            decimalFlag = true;
        } else if (c >= '0' && c <= '9') {
            digitFlag = true;
        } else {
            break;
        }
    }

    if (digitFlag) {
        return Token::Number;
    }

    return Token::Number;
}

Token Scanner::read() {
    // Skip whitespace
    while (m_current != m_end && isspace(*m_current)) {
        ++m_current;
    }

    // Check if we've reached the end of the file
    if (m_current == m_end) {
        return Token::EndOfFile;
    }

    char c = *m_current;

    // Operators
    if ('+' == c) {
        ++m_current;
        return Token::Add;
    }
    if ('-' == c) {
        ++m_current;
        return Token::Subtract;
    }
    if ('*' == c) {
        ++m_current;
        return Token::Multiply;
    }
    if ('/' == c) {
        ++m_current;
        return Token::Divide;
    }
    // Parentheses
    if ('(' == c) {
        ++m_current;
        return Token::LeftParen;
    }
    if (')' == c) {
        ++m_current;
        return Token::RightParen;
    }

    // Check if we're reading a number
    if ('.' == c || isdigit(c)) {
        // read the whole number
        while (m_current != m_end && (isdigit(*m_current) || '.' == *m_current)) {
            ++m_current;
        }

        return Token::Number;
    }

    return Token::Invalid;
}
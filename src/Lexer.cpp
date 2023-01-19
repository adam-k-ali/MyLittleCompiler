//
// Created by Adam Ali on 16/01/2023.
//

#include <utility>
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

void Lexer::consume(char expected, const std::string& message) {
    // If the current character is the expected character, advance the pointer
    if (*m_current == expected) {
        advance();
    } else {
        // Otherwise, throw an error
        throw LexerError(message, line, column);
    }

}

int Lexer::skipWhitespace() {
    // Keep track of the number of characters skipped
    int count = 0;

    std::vector<char> skipChars = {' ', '\t', '\n', '\r', '\f'};
    while(m_current != m_end) {
        // If the current character is a whitespace character, skipWhitespace it
        if (std::find(skipChars.begin(), skipChars.end(), *m_current) != skipChars.end()) {
            advance();
            ++count;
        } else {
            break;
        }
    }

    return count;
}

int Lexer::skipComment() {
    if (m_current + 1 >= m_end) {
        return 0;
    }

    // Keep track of the number of characters skipped
    int count = 0;

    // If the current character is a forward slash, check if the next character is a forward slash
    if (*m_current == '/' && *(m_current + 1) == '/') {
        // If it is, skipWhitespace the rest of the line
        while (m_current != m_end) {
            if (*m_current == '\n') {
                break;
            }
            advance();
            ++count;
        }
    }
    return count;
}

std::string Lexer::readWord() {
    // Move to the start of the word by skipping whitespace

    // Create a string to store the word
    std::string word;
    // While the current character is alphanumeric or an underscore, add it to the word
    while (m_current != m_end && (isalnum(*m_current) || *m_current == '_')) {
        word += *m_current;
        advance();
    }
    return word;
}

Token Lexer::readKeywordIdentifier() {
    std::string word = readWord();
    // Check if the word is a keyword
    if (NameToKeyword.find(word) != NameToKeyword.end()) {
        return {NameToKeyword.at(word), line, column};
    }

    // Otherwise, return it as an identifier
    return {TokenTypes::T_IDENTIFIER, new std::string(word), line, column};
}

Token Lexer::readNumber() {
    bool isDecimal = false;

    std::string number;

    /*
     * While the current character is a digit, or a decimal point when isDecimal is false,
     * add it to the number
     */
    while (m_current != m_end && (std::isdigit(*m_current) || (!isDecimal && *m_current == '.'))) {
        if (*m_current == '.') {
            isDecimal = true;
        }
        number += *m_current;
        advance();
    }

    // If the number is followed by a second decimal point, throw an error
    if (*m_current == '.') {
        throw LexerError("Unexpected character '.'", line, column);
    }

    return {isDecimal ? TokenTypes::T_DECIMAL : TokenTypes::T_INTEGER, new std::string(number), line, column};
}

Token Lexer::readString() {
    // Create a string to store the string
    std::string string;
    // While the current character is not a double quote, add it to the string
    while(m_current != m_end && *m_current != '"') {
        string += *m_current;
        advance();
    }
    // Check the next character is a double quote
    consume('"', "Expected '\"'");

    return {TokenTypes::T_STRING, new std::string(string), line, column};
}

Token Lexer::read() {
    int skipped;
    while (m_current != m_end) {
        skipped = skipWhitespace();
        skipped += skipComment();
        if (skipped == 0) {
            break;
        }
    }

    if (m_current == m_end) {
        // If the current pointer is at the end of the file, return an EOF token
        return {TokenTypes::T_EOF, line, column};
    }

    char c = *m_current;

    if (SymbolToToken.find(c) != SymbolToToken.end()) {
        // If the current character is a symbol, return the corresponding token
        advance();
        return {SymbolToToken.at(c), line, column};
    }

    if (std::isdigit(c)) {
        // If the current character is a digit, read a number
        return readNumber();
    }

    if (c == '"') {
        // If the current character is a double quote, read a string
        advance();
        return readString();
    }

    if (std::isalpha(c)) {
        // If the current character is a letter, read a keyword or identifier

        return readKeywordIdentifier();
    }


}
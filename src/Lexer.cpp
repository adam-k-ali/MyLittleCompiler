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
    return {TokenTypes::TL_IDENTIFIER, new std::string(word), line, column};
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

    return {isDecimal ? TokenTypes::TL_DECIMAL : TokenTypes::TL_INTEGER, new std::string(number), line, column};
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

    return {TokenTypes::TL_STRING, new std::string(string), line, column};
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

    char current_char = *m_current;
    char next_char = m_current + 1 < m_end ? *(m_current + 1) : '\0';
    char next_next_char = m_current + 2 < m_end ? *(m_current + 2) : '\0';

    // Handle symbols of length 1 to 3
    std::string symbol1 = std::string(1, current_char);
    std::string symbol2 = std::string(1, current_char) + std::string(1, next_char);
    std::string symbol3 = std::string(1, current_char) + std::string(1, next_char) + std::string(1, next_next_char);

    if (SymbolToToken.find(symbol3) != SymbolToToken.end()) {
        advance();
        advance();
        advance();
        return {SymbolToToken.at(symbol3), line, column};
    } else if (SymbolToToken.find(symbol2) != SymbolToToken.end()) {
        advance();
        advance();
        return {SymbolToToken.at(symbol2), line, column};
    } else if (SymbolToToken.find(symbol1) != SymbolToToken.end()) {
        advance();
        return {SymbolToToken.at(symbol1), line, column};
    }


    if (std::isdigit(current_char)) {
        // If the current character is a digit, read a number
        return readNumber();
    }

    if (current_char == '"') {
        // If the current character is a double quote, read a string
        advance();
        return readString();
    }

    if (std::isalpha(current_char)) {
        // If the current character is a letter, read a keyword or identifier

        return readKeywordIdentifier();
    }

    return {TokenTypes::T_INVALID, line, column};
}
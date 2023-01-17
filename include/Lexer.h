//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H
#include "Token.h"
#include "FileMap.h"

class LexerError : public std::exception {
private:
    std::string message;
    int line;
    int column;
public:
    LexerError(std::string message, int line, int column) {
        // Add the line and column to the message
        this->message = "LexerError: " +  message + " at line " + std::to_string(line) + " column " + std::to_string(column);
        this->line = line;
        this->column = column;
    };

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class Lexer {
private:
    const char* m_begin;
    const char* m_end;
    const char* m_current;

    int column = 0;
    int line = 1;

    /**
     * Moves the current pointer to the next character
     */
    void advance();

    /**
     * Skips all whitespace characters
     * @return The number of characters skipped
     */
    int skip();

    /**
     * Reads a keyword from the input
     * @param token The token to check if it is a keyword
     * @return The keyword token if it is a keyword, otherwise an invalid token.
     */
    Token readKeyword(Token token);

    /**
     * Reads an identifier from the input.
     * @return The identifier token
     */
    Token readIdentifier();

    /**
     * Reads a number from the input.
     * @return The number token
     */
    Token readNumber();
public:
    Lexer(const char* m_begin, const char* m_end) : m_begin(m_begin), m_end(m_end), m_current(m_begin) {}

    std::vector<Token> getTokens();

    /**
     * Reads the next token from the file
     * @return The next token
     */
    Token read();

    /**
     * Returns the current column in the file
     * @return
     */
    const char* current() const {
        return m_current;
    }

    /**
     * Returns the beginning of the file
     * @return
     */
    const char* begin() const {
        return m_begin;
    }

    /**
     * Returns the end of the file
     * @return
     */
    const char* end() const {
        return m_end;
    }
};


#endif //COMPILER_LEXER_H

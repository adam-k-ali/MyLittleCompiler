//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H
#include "FileMap.h"
#include "Token.h"

class LexerError : public std::exception {
private:
    std::string message;
    int line;
    int column;
public:
    LexerError(const std::string& message, int line, int column) {
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

    std::vector<Token> m_tokens;

    int column = 0;
    int line = 1;

    /**
     * Moves the current pointer to the next character
     */
    void advance();

    /**
     * Consumes a character, throwing an error if it doesn't match the expected character
     * @param expected The expected character
     * @param message The error message
     */
    void consume(char expected, const std::string& message);

    /**
     * Skips all whitespace characters
     * @return The number of characters skipped
     */
    int skipWhitespace();

    /**
     * Skip all comments
     * @return The number of characters skipped
     */
    int skipComment();

    /**
     * Reads a word from the current position
     * @return The word
     */
    std::string readWord();

    /**
     * Reads a keyword or identifier from the current position
     * @return The keyword or identifier
     */
    Token readKeywordIdentifier();

    /**
    * Reads a number from the current position
    * @return The number
    */
    Token readNumber();

    /**
     * Reads a string from the current position
     * @return The string
     */
    Token readString();


public:
    Lexer(const char* m_begin, const char* m_end) : m_begin(m_begin), m_end(m_end), m_current(m_begin) {}


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

    bool hasNext() {
        return m_current != m_end;
    }
};


#endif //COMPILER_LEXER_H

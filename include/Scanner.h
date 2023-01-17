//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H
#include "Token.h"
#include "FileMap.h"

class Scanner {
private:
    const char* m_begin;
    const char* m_end;
    const char* m_current;

    int skip();

    Token readKeyword();
    Token readIdentifier();

    Token readNumber();
public:
    Scanner(const char* m_begin, const char* m_end) : m_begin(m_begin), m_end(m_end), m_current(m_begin) {}

    std::vector<Token> getTokens();

    /**
     * Reads the next token from the file
     * @return The next token
     */
    Token read();

    /**
     * Returns the current position in the file
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


#endif //COMPILER_SCANNER_H

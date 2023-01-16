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

    Token readNumber();
public:
    Scanner(const char* m_begin, const char* m_end) : m_begin(m_begin), m_end(m_end), m_current(m_begin) {}

    Token read();

    const char* current() const {
        return m_current;
    }

    const char* begin() const {
        return m_begin;
    }

    const char* end() const {
        return m_end;
    }
};


#endif //COMPILER_SCANNER_H

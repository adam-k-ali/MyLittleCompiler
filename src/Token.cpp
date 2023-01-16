//
// Created by Adam Ali on 16/01/2023.
//

#include "Token.h"

const char* tokenToString(Token token) {
    switch (token) {
        case Token::Invalid: return "Invalid";
        case Token::EndOfFile: return "EndOfFile";
        case Token::Number: return "Number";
        case Token::Add: return "Add";
        case Token::Subtract: return "Subtract";
        case Token::Multiply: return "Multiply";
        case Token::Divide: return "Divide";
        case Token::LeftParen: return "LeftParen";
        case Token::RightParen: return "RightParen";
    }
}

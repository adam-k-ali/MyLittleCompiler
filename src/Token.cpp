//
// Created by Adam Ali on 16/01/2023.
//

#include "Token.h"

std::string Token::toString() const {
    std::string result = "";
    switch(type) {
        case TokenType::Invalid:
            result = "Invalid";
            break;
        case TokenType::EndOfFile:
            result = "EndOfFile";
            break;
        case TokenType::Number:
            result = "Number";
            break;
        case TokenType::String:
            result = "String";
            break;
        case TokenType::True:
            result = "True";
            break;
        case TokenType::False:
            result = "False";
            break;
        case TokenType::Nil:
            result = "Nil";
            break;
        case TokenType::Add:
            result = "Add";
            break;
        case TokenType::Subtract:
            result = "Subtract";
            break;
        case TokenType::Multiply:
            result = "Multiply";
            break;
        case TokenType::Divide:
            result = "Divide";
            break;
        case TokenType::Minus:
            result = "Minus";
            break;
        case TokenType::Bang:
            result = "Bang";
            break;
        case TokenType::BangEqual:
            result = "BangEqual";
            break;
        case TokenType::EqualEqual:
            result = "EqualEqual";
            break;
        case TokenType::Greater:
            result = "Greater";
            break;
        case TokenType::GreaterEqual:
            result = "GreaterEqual";
            break;
        case TokenType::Less:
            result = "Less";
            break;
        case TokenType::LessEqual:
            result = "LessEqual";
            break;
        case TokenType::LeftParen:
            result = "LeftParen";
            break;
        case TokenType::RightParen:
            result = "RightParen";
            break;
    }

    if (lexeme != nullptr) {
        result += "(" + std::string(lexeme) + ")";
    }

    return result;
}

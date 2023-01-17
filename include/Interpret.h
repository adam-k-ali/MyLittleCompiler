//
// Created by Adam Ali on 17/01/2023.
//
#include "Token.h"

double interpretAST(struct ASTNode* root) {
    double left, right;

    if (root->left) {
        left = interpretAST(root->left);
    }
    if (root->right) {
        right = interpretAST(root->right);
    }

    switch(root->type) {
        case TokenType::Invalid:
            return 0;
        case TokenType::EndOfFile:
            return 0;
        case TokenType::Number:
            return *(double*)root->value;
        case TokenType::Add:
            return left + right;
        case TokenType::Minus:
            return left - right;
        case TokenType::String:
            break;
        case TokenType::True:
            break;
        case TokenType::False:
            break;
        case TokenType::Nil:
            break;
        case TokenType::Star:
            return left * right;
        case TokenType::Slash:
            return left / right;
        case TokenType::Bang:
            break;
        case TokenType::BangEqual:
            break;
        case TokenType::EqualEqual:
            break;
        case TokenType::Greater:
            break;
        case TokenType::GreaterEqual:
            break;
        case TokenType::Less:
            break;
        case TokenType::LessEqual:
            break;
        case TokenType::LeftParen:
            break;
        case TokenType::RightParen:
            break;
    }

    return 0;
}
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
        case TokenType::Plus:
            return left + right;
        case TokenType::Minus:
            return left - right;
        case TokenType::Star:
            return left * right;
        case TokenType::Slash:
            return left / right;
    }

    return 0;
}
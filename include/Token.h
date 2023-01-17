//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <string>
#include <map>
#include "defs.h"

struct ASTNode {
    TokenType type;
    void* value;
    Types dtype;
    ASTNode* left;
    ASTNode* right;

    // Build a leaf node
    ASTNode(TokenType type, void* value, Types dtype) {
        this->type = type;
        this->value = value;
        this->dtype = dtype;
        this->left = nullptr;
        this->right = nullptr;
    }

    // Build a generic AST node
    ASTNode(TokenType type, Types dtype, ASTNode* left, ASTNode* right) {
        this->type = type;
        this->value = nullptr;
        this->dtype = dtype;
        this->left = left;
        this->right = right;
    }

    // Build a node with only 1 child
    ASTNode(TokenType type, void* value, Types dtype, ASTNode* left) {
        this->type = type;
        this->value = value;
        this->dtype = dtype;
        this->left = left;
        this->right = nullptr;
    }
    /**
     * Convert AST to string
     * @return
     */
    std::string toString() const {
        std::string result = "";

        if (dtype == Types::Nil) {
            result += "nil";
        } else if (dtype == Types::Bool) {
            result += *(bool*)value ? "true" : "false";
        } else if (dtype == Types::Double) {
            result += std::to_string(*(double*)value);
        } else if (dtype == Types::String) {
            result += *(std::string*)value;
        }

        return result;
    }

};

class Token {
private:
    TokenType type;
    char* value;
public:
    Token(TokenType type, char* value) : type(type), value(value) {};
    Token(TokenType type) : type(type), value(nullptr) {};

    TokenType getType() const { return type; }
    char* getValue() const { return value; }
};


#endif //COMPILER_TOKEN_H

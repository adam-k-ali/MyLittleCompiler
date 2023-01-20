//
// Created by Adam Ali on 20/01/2023.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H
#include "Token.h"
#include <vector>
#include <string>

struct ASTNode {
    TokenTypes type;
    void* value;
    std::vector<ASTNode> children;
    ASTNode(TokenTypes type, void* value) {
        this->type = type;
        this->value = value;
    }

    ASTNode(TokenTypes type, void* value, std::vector<ASTNode> children) {
        this->type = type;
        this->value = value;
        this->children = children;
    }

    std::string toString() {
        std::string str = "";
        std::string value = "";
        if (this->value != nullptr) {
            value = std::string((char*) this->value);
        }
        str += "Type: " + TokenToString[type] + " Value: " + value + " # Children: " + std::to_string(children.size());
        return str;
    }
};

class ParserError : public std::exception {
private:
    std::string message;
    int line;
    int column;
public:
    ParserError(const std::string& message, int line, int column) {
        // Add the line and column to the message
        this->message = "ParserError: " + message + " at line " + std::to_string(line) + " column " + std::to_string(column);
        this->line = line;
        this->column = column;
    };

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class Parser {
private:
    std::vector<Token> m_tokens;
    size_t m_current = 0;
    size_t m_line = 1;
    size_t m_column = 1;

    /**
     * Returns the current token
     * @return The current token
     */
    Token peek();

    /**
     * Returns the previous token
     * @return The previous token
     */
    Token previous();

    /**
     * Returns the next token
     * @return The next token
     */
    Token next();

    /**
     * Moves to the next token
     * @return The next token
     */
    Token advance();

    /**
     * Checks if the parser has reached the end of the file
     * @return True if the parser has reached the end of the file
     */
    bool isAtEnd();

    /**
     * Checks if the current token is of the given type
     * @param type The type to check
     * @return True if the current token is of the given type
     */
    bool check(TokenTypes type);

    /**
     * Checks if the current token matches any of the given types.
     * If it does, it will return true and advance the current token.
     * @param types The types to check
     * @return True if the current token matches any of the given types
     */
    bool match(std::vector<TokenTypes> types);

    /**
     * Consumes a token, throwing an error if it doesn't match the expected type
     * @param type The expected type
     * @param message The error message
     */
    void consume(TokenTypes type, const std::string& message);

    /**
     * Get the precedence of the given operator
     * @param type The operator type
     * @return The precedence of the given operator
     */
    int getPrecedence(TokenTypes type);

    /**
     * Parses a literal
     * @return The parsed literal
     */
    ASTNode* literal();

    /**
     * Parses a binary expression
     * @return The parsed binary expression
     */
     ASTNode* binary();

     /**
      * Parses a package declaration
      * @return The parsed package declaration
      */
      ASTNode* packageDeclaration();

      /**
       * Parses include statements
       * @return The parsed include statements
       */
       std::vector<ASTNode*> includeStatements();

       /**
        * Parses class, enum and struct declarations
        * @return The parsed class, enum or struct declaration
        */
       ASTNode* structureDeclaration();

public:
    /**
     * Creates a new parser
     * @param tokens The tokens to parse
     */
    explicit Parser(const std::vector<Token>& tokens) : m_tokens(tokens) {};

    /**
     * Parses the tokens
     * @return The parse Abstract Syntax Trees
     */
    std::vector<ASTNode*> parse();
};


#endif //COMPILER_PARSER_H

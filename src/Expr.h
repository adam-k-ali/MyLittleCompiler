//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_EXPR_H
#define COMPILER_EXPR_H


#include "Token.h"

enum class Constants {
    Nil,
    Bool,
    Double,
    String,
};

/**
 * Class for all expressions.
 * expr -> equality
 */
class Expr {
public:
    virtual std::string toString() const = 0;
};

/**
 * Class for literal expressions.
 */
class LiteralExpr : public Expr {
private:
    void *value;
    Constants dtype;
public:
    explicit LiteralExpr(void *value, Constants dtype) : value(value), dtype(dtype) {};

    std::string toString() const override {

        std::string result = "";
        if (dtype == Constants::Nil) {
            result += "nil";
        } else if (dtype == Constants::Bool) {
            result += *(bool *) value ? "true" : "false";
        } else if (dtype == Constants::Double) {
            result += std::to_string(*(double *) value);
        } else if (dtype == Constants::String) {
            result += *(std::string *) value;
        }

        return result;
    }
};

/**
 * Class for grouping expressions.
 * expr -> "(" expr ")"
 */
class GroupingExpr : public Expr {
private:
    Expr *expression;
public:
    explicit GroupingExpr(Expr *expression) : expression(expression) {};

    std::string toString() const override {
        return "(" + expression->toString() + ")";
    }
};

/**
 * Class for all primary expressions.
 * primary -> NUMBER | STRING | true | false | nil | ( expr )
 */
class PrimaryExpr : public Expr {
private:
    Token token;
public:
    explicit PrimaryExpr(Token token) : token(token) {};

    std::string toString() const override {
        return token.toString();
    }
};

/**
 * Class for all unary expressions.
 * unary -> ( "-" | "!" ) unary | primary
 */
class UnaryExpr : public Expr {
private:
    Token token;
    Expr *expr;
public:
    UnaryExpr(Token token, Expr *expr) : token(token), expr(expr) {};
    std::string toString() const override {
        return token.toString() + expr->toString();
    }
};

/**
 * Class for binary expressions
 */
class BinaryExpr : public Expr {
private:
    Expr *left;
    Token token;
    Expr *right;
public:
    BinaryExpr(Expr *left, Token token, Expr *right) : left(left), token(token), right(right) {};

    std::string toString() const override {
        return "(" + left->toString() + " " + token.toString() + " " + right->toString() + ")";
    }
};

/**
 * Class for all term expressions.
 * term -> factor ( ( "-" | "+" ) factor )*
 */
class TermExpr : public Expr {
private:
    Expr *left;
    Token token;
    Expr *right;
public:
    TermExpr(Expr *left, Token token, Expr *right) : left(left), token(token), right(right) {};

    std::string toString() const override {
        return "(" + left->toString() + " " + token.toString() + " " + right->toString() + ")";
    }
};

/**
 * Class for all comparison expressions.
 */
class ComparisonExpr : public Expr {
private:
    Expr *left;
    Token token;
    Expr *right;
public:
    ComparisonExpr(Expr *left, Token token, Expr *right) : left(left), token(token), right(right) {};

    std::string toString() const override {
        return "(" + left->toString() + " " + token.toString() + " " + right->toString() + ")";
    }
};

/**
 * Class for all equality expressions.
 * equality -> comparison ( ( "!=" | "==" ) comparison )*
 */
 class EqualityExpr : public Expr {
private:
    Expr *left;
    Token token;
    Expr *right;
public:
    EqualityExpr(Expr *left, Token token, Expr *right) : left(left), token(token), right(right) {};

    std::string toString() const override {
        return "(" + left->toString() + " " + token.toString() + " " + right->toString() + ")";
    }
 };
#endif //COMPILER_EXPR_H

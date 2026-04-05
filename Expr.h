
#ifndef EXPR_H
#define EXPR_H
#include <memory>
#include <any>
#include "Token.h"

class Expr {
public:
    virtual ~Expr() = default;
};
    
class Binary : public Expr {
public:
    Binary (std::unique_ptr<Expr> left, Token oper, std::unique_ptr<Expr> right)
    : left(std::move(left)), oper(std::move(oper)), right(std::move(right)){}

    const std::unique_ptr<Expr> left;
    const Token oper;
    const std::unique_ptr<Expr> right;
};

class Grouping : public Expr {
public:
    Grouping (std::unique_ptr<Expr> expression)
    : expression(std::move(expression)){}

    const std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
    Literal (std::any value)
    : value(std::move(value)){}

    const std::any value;
};

class Unary : public Expr {
public:
    Unary (Token oper, std::unique_ptr<Expr> right)
    : oper(std::move(oper)), right(std::move(right)){}

    const Token oper;
    const std::unique_ptr<Expr> right;
};

#endif

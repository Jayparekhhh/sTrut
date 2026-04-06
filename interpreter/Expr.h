
#ifndef EXPR_H
#define EXPR_H
#include <memory>
#include <any>
#include "Token.h"
    
class Binary;
class Grouping;
class Literal;
class Unary;
class Visitor {
public:
    virtual std::any visitBinaryExpr(Binary& expr) = 0;
    virtual std::any visitGroupingExpr(Grouping& expr) = 0;
    virtual std::any visitLiteralExpr(Literal& expr) = 0;
    virtual std::any visitUnaryExpr(Unary& expr) = 0;
    virtual ~Visitor() = default;
};
    
class Expr{
public:
    virtual ~Expr() = default;
    virtual std::any accept(Visitor &visitor) = 0;
};

class Binary : public Expr {
public:
    Binary (std::unique_ptr<Expr> left, Token oper, std::unique_ptr<Expr> right)
    : left(std::move(left)), oper(std::move(oper)), right(std::move(right)){}

    std::any accept(Visitor &visitor) override {
        return visitor.visitBinaryExpr(*this);
    }

    const std::unique_ptr<Expr> left;
    const Token oper;
    const std::unique_ptr<Expr> right;
};

class Grouping : public Expr {
public:
    Grouping (std::unique_ptr<Expr> expression)
    : expression(std::move(expression)){}

    std::any accept(Visitor &visitor) override {
        return visitor.visitGroupingExpr(*this);
    }

    const std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
    Literal (std::any value)
    : value(std::move(value)){}

    std::any accept(Visitor &visitor) override {
        return visitor.visitLiteralExpr(*this);
    }

    const std::any value;
};

class Unary : public Expr {
public:
    Unary (Token oper, std::unique_ptr<Expr> right)
    : oper(std::move(oper)), right(std::move(right)){}

    std::any accept(Visitor &visitor) override {
        return visitor.visitUnaryExpr(*this);
    }

    const Token oper;
    const std::unique_ptr<Expr> right;
};

#endif

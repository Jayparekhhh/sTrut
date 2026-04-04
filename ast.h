//
// Created by jay20 on 05-04-2026.
//

#ifndef AST_H
#define AST_H
#include "Token.h"

class Expr {
public:
    const Expr left;
    const Token operator;
    const Expr right;
};

class Binary : public Expr {
    Binary(Expr left, )
};
#endif //AST_H

//
// Created by jay20 on 07-04-2026.
//
#include <memory>
#include <any>
#include <iostream>
#include "Token.h"
#include "Expr.h"

class AstPrinter : public Visitor {
public:
    std::string print(Expr& expr) {
        return std::any_cast<std::string>(expr.accept(*this));
    }
    std::any visitBinaryExpr(Binary &expr) override {
        return bracketd(expr.oper.lexeme, )
    }
};


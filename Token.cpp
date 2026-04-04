//
// Created by jay20 on 19-03-2026.
//
#include <string>
#include <any>
#include "TokenType.h"
#include "Token.h"

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
    : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {}

std::string Token::toString() {
    std::string literalStr;
    if (!literal.has_value())
        literalStr = "null";

    else if (literal.type()==typeid(std::string))
        literalStr = std::any_cast<std::string>(literal);

    else if (literal.type()==typeid(double))
       literalStr = std::to_string(std::any_cast<double>(literal));

    else if (literal.type() == typeid(bool))
       literalStr = std::any_cast<bool>(literal) ? "true" : "false";

    return std::to_string(static_cast<int>(type)) + " " +  lexeme + " " + literalStr;
}

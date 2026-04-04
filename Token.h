//
// Created by jay20 on 23-03-2026.
//
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <any>

class Token {
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;
public:
    Token(TokenType type, std::string lexeme, std::any literal, int line);
    std::string toString();
};
#endif //TOKEN_H

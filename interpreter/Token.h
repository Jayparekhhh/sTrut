//
// Created by jay20 on 23-03-2026.
//
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <any>

class Token {
public:
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;
    Token(TokenType type, std::string lexeme, std::any literal, int line);
    std::string toString();
};
#endif //TOKEN_H

//
// Created by jay20 on 23-03-2026.
//

#ifndef SCANNER_H
#define SCANNER_H
#include <vector>
#include <string>
#include "TokenType.h"
#include "Token.h"
#include <any>
class Scanner {
private:
    std::string source;
    std::vector<Token> tokens;

public:
    int start = 0;
    int current = 0;
    int line = 1;

    std::vector<Token> scanTokens();

    Scanner(std::string source);

    void scanToken();

    bool isAtEnd();

    void addToken(TokenType type);

    char next();

    void addToken(TokenType type, std::any literal);

    char cur_char();

    void get_string();

    char next_char();

    void number();

    bool alpha(char c);

    void identifier();

    bool isalphanum(char c);

    void dec_cur();
};
#endif //SCANNER_H

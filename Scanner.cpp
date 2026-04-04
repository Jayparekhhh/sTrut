//
// Created by jay20 on 23-03-2026.
//
#include <string>
#include <vector>

#include "TokenType.h"
#include "Token.h"
#include "Scanner.h"

#include <iostream>
#include <unordered_map>

static const std::unordered_map<std::string, TokenType> keywords = {
    {"and",    TokenType::AND},
    {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"fun",    TokenType::FUN},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE}
};

Scanner::Scanner(std::string source) : source(std::move(source)) {}

bool Scanner::isAtEnd() {
    return current>=source.size();
}

char Scanner::next() {
    if (isAtEnd()) return '\0';
    return source[current++];
}

void Scanner::dec_cur() {
    if (isAtEnd()) return;
    current--;
}
void Scanner::addToken(TokenType type, std::any literal) {

    std::string current_lexeme = source.substr(start,current-start);
    tokens.emplace_back(type, current_lexeme, std::move(literal), line);
}
void Scanner::addToken(TokenType type) {
    addToken(type,nullptr);
}

char Scanner::cur_char() {
    if (isAtEnd()) return '\0';
    return source[current];

}
void Scanner::get_string() {
    while (cur_char()!='"') {
        if (cur_char()=='\n') line++;
        next();

        if (isAtEnd()) {
            std::cerr <<"Line "<< line <<" Error: Unterminated string."<<std::endl;
            return;
        }
    }
    next();
    std::string str = source.substr(start + 1, current - 2 - start );
    addToken(TokenType::STRING, str);
}

char Scanner::next_char() {
    if (current + 1>=source.length()) return '\0';
    return source[current+1];
}
void Scanner::number() {
    while (cur_char()>='0'&&cur_char()<='9') next();
    if (cur_char()=='.'&& (next_char()>='0'&&next_char()<='9')) {
        next();
        while (cur_char()>='0'&&cur_char()<='9') next();
    }
    addToken(TokenType::NUMBER,std::stod(source.substr(start,current-start)));
}

bool Scanner::alpha(char c) {
    return (c>='a' && c<='z') || (c>='A' && c<='Z') || c=='-';
}
bool Scanner::isalphanum(char c) {
    return alpha(c) || (c>='0'&& c<='9');
}
void Scanner::identifier() {
    while (isalphanum(cur_char())) next();

    std::string text = source.substr(start,current-start);
    auto it = keywords.find(text);
    if (it==keywords.end()) addToken(TokenType::IDENTIFIER);

    else addToken(it->second);
}
void Scanner::scanToken() {
    char c =  next();
    switch (c) {
        //single character
        case '(':
            addToken(TokenType::LEFT_PAREN); break;
        case ')':
            addToken(TokenType::RIGHT_PAREN); break;
        case '{':
            addToken(TokenType::LEFT_BRACE); break;
        case '}':
            addToken(TokenType::RIGHT_BRACE); break;
        case ',':
            addToken(TokenType::COMMA); break;
        case '.':
            addToken(TokenType::DOT); break;
        case '-':
            addToken(TokenType::MINUS); break;
        case '+':
            addToken(TokenType::PLUS); break;
        case ';':
            addToken(TokenType::SEMICOLON); break;
        case '*':
            addToken(TokenType::STAR); break;

        //double character operators
        case '!': {
            char d = next();
            if (d =='=') addToken(TokenType::NOT_EQUAL);
            else {
                dec_cur();
                addToken(TokenType::NOT);
            }
            break;
        }
        case '=': {
            char d = next();
            if (d=='=') addToken(TokenType::EQUAL_EQUAL);
            else if (d=='>') addToken(TokenType::GREATER_EQUAL);
            else if (d=='<') addToken(TokenType::LESS_EQUAL);
            else if (d=='!') addToken(TokenType::NOT_EQUAL);
            else {
                dec_cur();
                addToken(TokenType::EQUAL);
            }
            break;
        }
        case '>': {
            char d = next();
            if (d =='=') addToken(TokenType::GREATER_EQUAL);
            else {
                dec_cur();
                addToken(TokenType::GREATER);
            }
            break;
        }
        case '<': {
            char d = next();
            if (d =='=') addToken(TokenType::LESS_EQUAL);
            else {
                dec_cur();
                addToken(TokenType::LESS);
            }
            break;
        }
        case '/': {
            //comments
            char d = next();
            if (d=='/') {
                while (true) {
                    if (d=='\n') {
                        line++;
                        break;
                    }
                    if (d=='\0') break;
                    d = next();
                }
            }
            else {
                dec_cur();
                addToken(TokenType::SLASH);
            }
            break;
        }
        //Ignore whitespace
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        //string literal
        case '"':
            get_string();
            break;

        default: {
            if (c>='0'&&c<='9') {
                number();
                break;
            }
            else if (alpha(c)) {
                identifier();
            }
            else std::cerr << "[Line " <<line<<" Error: Unexpected character"<<std::endl;
            break;
        }
    }
}
std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(TokenType::EOF_TOKEN, "", nullptr, line);
    return tokens;
}


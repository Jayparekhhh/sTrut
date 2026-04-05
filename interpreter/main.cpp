#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Scanner.h"
#include "Token.h"
#include <vector>

void run(std::string &source);

void runFile(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr<<"Could not open file: "<<path<<std::endl;
        exit(74);
    }
    std::string source;
    std::string line;
    while (std::getline(file,line)) {
        source+=line + '\n';
    }
    run(source);
}
void runPrompt() {
    std::string line;
    while (true) {
        std::cout<<">>> ";
        if (!std::getline(std::cin, line)||line=="exit") {
            break;
        }
        run(line);
    }
}
void run(std::string &source) {
    Scanner scanner(source);

    std::vector<Token> tokens = scanner.scanTokens();

    for (auto token: tokens) {
        std::cout << token.toString() << std::endl;
    }
}
int main(const int argc, char* argv[]) {
    if (argc>2) {
        std::cout<<"Invalid Input"<<std::endl;
        exit(0);
    }
    else if (argc==2) {
        runFile(argv[1]);
    }
    else {
        runPrompt();
    }
    return 0;
}
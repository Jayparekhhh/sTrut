cmake_minimum_required(VERSION 3.25)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        main.cpp
        interpreter/TokenType.h
        interpreter/Token.cpp
        interpreter/Scanner.cpp
        interpreter/Token.h
        interpreter/Scanner.h
        interpreter/ast.cpp
        interpreter/ast.h)

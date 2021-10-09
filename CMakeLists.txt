cmake_minimum_required(VERSION 3.16)
project(Parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(Parser main.cpp Parser.cpp Parser.h MyOutput.cpp MyOutput.h Lexer.cpp MyException.cpp MyOutput.cpp MyOutput.h)

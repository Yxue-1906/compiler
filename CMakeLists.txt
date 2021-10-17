cmake_minimum_required(VERSION 3.16)
project(Parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(Parser main.cpp Parser/Parser.cpp Parser/Parser.h Lexer/Lexer.cpp Exception/MyException.cpp Lexer/Token.cpp Lexer/Token.h Output/MyOutput.cpp Output/MyOutput.h Lexer/Token/IDENFR.h Lexer/Token/INTCON.h Lexer/Token/STRCON.h Lexer/Token/MAINTK.h Lexer/Token/CONSTTK.h Lexer/Token/INTTK.h Lexer/Token/BREAKTK.h Lexer/Token/CONTINUETK.h Lexer/Token/IFTK.h Lexer/Token/ELSETK.h Lexer/Token/NOT.h Lexer/Token/AND.h Lexer/Token/OR.h Lexer/Token/WHILETK.h Lexer/Token/GETINTTK.h Lexer/Token/PRINTFTK.h Lexer/Token/RETURNTK.h Lexer/Token/PLUS.h Lexer/Token/MINU.h Lexer/Token/VOIDTK.h Lexer/Token/MULT.h Lexer/Token/DIV.h Lexer/Token/MOD.h Lexer/Token/LSS.h Lexer/Token/LEQ.h Lexer/Token/GRE.h Lexer/Token/GEQ.h Lexer/Token/EQL.h Lexer/Token/NEQ.h Lexer/Token/ASSIGN.h Lexer/Token/SEMICN.h Lexer/Token/COMMA.h Lexer/Token/LPARENT.h Lexer/Token/RPARENT.h Lexer/Token/LBRACK.h Lexer/Token/RBRACK.h Lexer/Token/LBRACE.h Lexer/Token/RBRACE.h Parser/GramNode.cpp Parser/GramNode.h Parser/GramNode/CompUnit.cpp Parser/GramNode/CompUnit.h)

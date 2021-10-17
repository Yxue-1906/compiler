//
// Created by unrelated on 2021/10/17.
//

#include "Token.h"

const std::map<int, std::string> Token::type2Name = {
        {1,  "IDENFR"},
        {2,  "INTCON"},
        {3,  "STRCON"},
        {4,  "MAINTK"},
        {5,  "CONSTTK"},
        {6,  "INTTK"},
        {7,  "BREAKTK"},
        {8,  "CONTINUETK"},
        {9,  "IFTK"},
        {10, "ELSETK"},
        {11, "NOT"},
        {12, "AND"},
        {13, "OR"},
        {14, "WHILETK"},
        {15, "GETINTTK"},
        {16, "PRINTFTK"},
        {17, "RETURNTK"},
        {18, "PLUS"},
        {19, "MINU"},
        {20, "VOIDTK"},
        {21, "MULT"},
        {22, "DIV"},
        {23, "MOD"},
        {24, "LSS"},
        {25, "LEQ"},
        {26, "GRE"},
        {27, "GEQ"},
        {28, "EQL"},
        {29, "NEQ"},
        {30, "ASSIGN"},
        {31, "SEMICN"},
        {32, "COMMA"},
        {33, "LPARENT"},
        {34, "RPARENT"},
        {35, "LBRACK"},
        {36, "RBRACK"},
        {37, "LBRACE"},
        {38, "RBRACE"},
        {39, "COMMENT"}
};

Token::Token(int type) : tokenType(type), tokenName(type2Name.at(type)) {}

std::string &Token::getTokenName() {
    return const_cast<std::string &>(this->tokenName);
}

int Token::getTokenType() {
    return this->tokenType;
}
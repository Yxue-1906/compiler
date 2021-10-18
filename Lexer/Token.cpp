//
// Created by unrelated on 2021/10/17.
//

#include "Token.h"

int Token::IDENFR = 1;
int Token::INTCON = 2;
int Token::STRCON = 3;
int Token::MAINTK = 4;
int Token::CONSTTK = 5;
int Token::INTTK = 6;
int Token::BREAKTK = 7;
int Token::CONTINUETK = 8;
int Token::IFTK = 9;
int Token::ELSETK = 10;
int Token::NOT = 11;
int Token::AND = 12;
int Token::OR = 13;
int Token::WHILETK = 14;
int Token::GETINTTK = 15;
int Token::PRINTFTK = 16;
int Token::RETURNTK = 17;
int Token::PLUS = 18;
int Token::MINU = 19;
int Token::VOIDTK = 20;
int Token::MULT = 21;
int Token::DIV = 22;
int Token::MOD = 23;
int Token::LSS = 24;
int Token::LEQ = 25;
int Token::GRE = 26;
int Token::GEQ = 27;
int Token::EQL = 28;
int Token::NEQ = 29;
int Token::ASSIGN = 30;
int Token::SEMICN = 31;
int Token::COMMA = 32;
int Token::LPARENT = 33;
int Token::RPARENT = 34;
int Token::LBRACK = 35;
int Token::RBRACK = 36;
int Token::LBRACE = 37;
int Token::RBRACE = 38;
int Token::COMMENT = 39;

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

bool Token::isTypeOf(int type) {
    return this->tokenType == type;
}
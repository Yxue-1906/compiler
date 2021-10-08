//
// Created by unrelated on 2021/9/28.
//

#ifndef LEXER_MYDEFINATION_H
#define LEXER_MYDEFINATION_H

const int IDENFR = 1;
const int INTCON = 2;
const int STRCON = 3;
const int MAINTK = 4;
const int CONSTTK = 5;
const int INTTK = 6;
const int BREAKTK = 7;
const int CONTINUETK = 8;
const int IFTK = 9;
const int ELSETK = 10;
const int NOT = 11;
const int AND = 12;
const int OR = 13;
const int WHILETK = 14;
const int GETINTTK = 15;
const int PRINTFTK = 16;
const int RETURNTK = 17;
const int PLUS = 18;
const int MINU = 19;
const int VOIDTK = 20;
const int MULT = 21;
const int DIV = 22;
const int MOD = 23;
const int LSS = 24;
const int LEQ = 25;
const int GRE = 26;
const int GEQ = 27;
const int EQL = 28;
const int NEQ = 29;
const int ASSIGN = 30;
const int SEMICN = 31;
const int COMMA = 32;
const int LPARENT = 33;
const int RPARENT = 34;
const int LBRACK = 35;
const int RBRACK = 36;
const int LBRACE = 37;
const int RBRACE = 38;
const int COMMENT = 39;
const int OTHER = 40;

static std::map<int, std::string> name = {
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
#endif //LEXER_MYDEFINATION_H
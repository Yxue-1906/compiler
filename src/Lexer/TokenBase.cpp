//
// Created by unrelated on 2021/10/17.
//

#include "TokenBase.h"

int TokenBase::IDENFR = 1;
int TokenBase::INTCON = 2;
int TokenBase::STRCON = 3;
int TokenBase::MAINTK = 4;
int TokenBase::CONSTTK = 5;
int TokenBase::INTTK = 6;
int TokenBase::BREAKTK = 7;
int TokenBase::CONTINUETK = 8;
int TokenBase::IFTK = 9;
int TokenBase::ELSETK = 10;
int TokenBase::NOT = 11;
int TokenBase::AND = 12;
int TokenBase::OR = 13;
int TokenBase::WHILETK = 14;
int TokenBase::GETINTTK = 15;
int TokenBase::PRINTFTK = 16;
int TokenBase::RETURNTK = 17;
int TokenBase::PLUS = 18;
int TokenBase::MINU = 19;
int TokenBase::VOIDTK = 20;
int TokenBase::MULT = 21;
int TokenBase::DIV = 22;
int TokenBase::MOD = 23;
int TokenBase::LSS = 24;
int TokenBase::LEQ = 25;
int TokenBase::GRE = 26;
int TokenBase::GEQ = 27;
int TokenBase::EQL = 28;
int TokenBase::NEQ = 29;
int TokenBase::ASSIGN = 30;
int TokenBase::SEMICN = 31;
int TokenBase::COMMA = 32;
int TokenBase::LPARENT = 33;
int TokenBase::RPARENT = 34;
int TokenBase::LBRACK = 35;
int TokenBase::RBRACK = 36;
int TokenBase::LBRACE = 37;
int TokenBase::RBRACE = 38;
int TokenBase::COMMENT = 39;

std::vector<TokenBase *>::iterator TokenBase::end;
bool TokenBase::endSet = false;

const std::map<int, std::string> TokenBase::type2Name = {
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


TokenBase::TokenBase(int type)
        : tokenType(type), tokenName(type2Name.at(type)) {}

std::string &TokenBase::getTokenName() {
    return const_cast<std::string &>(this->tokenName);
}

int TokenBase::getTokenType() {
    return this->tokenType;
}

void TokenBase::setEnd(std::vector<TokenBase *>::iterator end) {
    if (!TokenBase::endSet) {
        TokenBase::end = end;
        TokenBase::endSet = true;
    }
}

bool TokenBase::isTypeOf(const std::vector<TokenBase *>::iterator &ite, int type) {
    return ite < TokenBase::end && (**ite).tokenType == type;
}

bool TokenBase::isTypeOf(const std::vector<TokenBase *>::iterator &&ite, int type) {
    return ite < TokenBase::end && (**ite).tokenType == type;
}

int TokenBase::setLineNumber(int lineNumber) {
    if (!lineNumberSet) {
        this->lineNumber = lineNumber;
        lineNumberSet = true;
    }
    return this->lineNumber;
}

int TokenBase::getLineNumber() const {
    return this->lineNumber;
}
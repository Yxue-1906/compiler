//
// Created by unrelated on 2021/9/28.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <fstream>
#include <functional>
#include <vector>
#include "Token.h"
#include "Token/NEQ.h"
#include "Token/NOT.h"
#include "Token/LPARENT.h"
#include "Token/MOD.h"
#include "Token/AND.h"
#include "Token/RPARENT.h"
#include "Token/MULT.h"
#include "Token/PLUS.h"
#include "Token/COMMA.h"
#include "Token/MINU.h"
#include "Token/DIV.h"
#include "Token/SEMICN.h"
#include "Token/LEQ.h"
#include "Token/LSS.h"
#include "Token/EQL.h"
#include "Token/ASSIGN.h"
#include "Token/GEQ.h"
#include "Token/GRE.h"
#include "Token/LBRACK.h"
#include "Token/RBRACK.h"
#include "Token/BREAKTK.h"
#include "Token/CONSTTK.h"
#include "Token/CONTINUETK.h"
#include "Token/ELSETK.h"
#include "Token/GETINTTK.h"
#include "Token/IFTK.h"
#include "Token/INTTK.h"
#include "Token/MAINTK.h"
#include "Token/PRINTFTK.h"
#include "Token/RETURNTK.h"
#include "Token/VOIDTK.h"
#include "Token/WHILETK.h"
#include "Token/LBRACE.h"
#include "Token/OR.h"
#include "Token/RBRACE.h"
#include "Token/IDENFR.h"
#include "Token/STRCON.h"
#include "Token/INTCON.h"

class Lexer {
    // should implement in singleton pattern
public:

private:
    static const int LINE_COMMENT = 0;
    static const int BLOCK_COMMENT = 1;
    std::vector<Token *> tokenList;
    bool inited = false;

    std::ifstream ifs;
    std::string now_line;
    std::string::iterator now_char_p;
    std::string::iterator now_look_forward_p;
    int line_count = 0;
    bool end = false;

public:
    Lexer(std::ifstream);

    ~Lexer();

    std::vector<Token *> &getList();

private:
    //bool isWhitespace(typeof(std::string::iterator));


    bool safeLookAhead(const std::string, std::function<bool(std::string::iterator)>);

    bool isAlNum(int);

    bool jumpSpace();

    bool jumpComment(int type);

    Token *getSymbol();

    IDENFR *getIdent();

    INTCON *getConst();

    STRCON *getStr();

    void init();

};


#endif //LEXER_LEXER_H

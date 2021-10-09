//
// Created by unrelated on 2021/9/28.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <fstream>
#include <functional>
#include "MyOutput.h"

class Lexer {
    // should implement in singleton pattern
public:

private:
    static const int LINE_COMMENT = 0;
    static const int BLOCK_COMMENT = 1;

    std::ifstream ifs;
    std::string now_line;
    std::string::iterator now_char_p;
    std::string::iterator now_look_forward_p;
    int line_count = 0;
    bool end = false;

    MyOutput lexerOutput{true};

public:
    //Lexer(std::ifstream);
    Lexer(std::string);

    ~Lexer();

    bool getWord(std::string **const, int *);

private:
    //bool isWhitespace(typeof(std::string::iterator));


    bool safeLookAhead(const std::string, std::function<bool(std::string::iterator)>);

    bool isAlNum(int);

    bool jumpSpace();

    bool jumpComment(int type);

    bool getSymbol(std::string *const, int *const);

    bool getIdent(std::string *const, int *const);

    bool getConst(std::string *const, int *const);

    bool getStr(std::string *const, int *const);

};


#endif //LEXER_LEXER_H

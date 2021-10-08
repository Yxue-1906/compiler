//
// Created by unrelated on 2021/9/28.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <fstream>

class Lexer {
    // should implement in singleton pattern
public:

private:
    std::ifstream ifs;
    std::string now_line;
    std::string::iterator now_char_p;
    int line_count = 0;
    bool end = false;

public:
    //Lexer(std::ifstream);
    Lexer(std::string);

    ~Lexer();

    bool getWord(std::string **const, int *);

private:
    //bool isWhitespace(typeof(std::string::iterator));

    bool isal_num(int ch);

    bool jumpSpace();

    bool jumpComment(int type);

    bool getSymbol(std::string *const, int *const);

    bool getIdent(std::string *const, int *const);

    bool getConst(std::string *const, int *const);

    bool getStr(std::string *const, int *const);

};


#endif //LEXER_LEXER_H

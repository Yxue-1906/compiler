//
// Created by unrelated on 2021/10/8.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "../Lexer/Lexer.h"
#include "../Exception/MyException.h"
#include "GramNode/CompUnit.h"

class Parser : MyOutput {
public:
    // public attributes

private:
    // private attributes
    std::vector<TokenBase *> &tokenList;
    GramNode *root;

public:
    // public methods
    Parser(std::vector<TokenBase *> &);

    void print();

private:
    // private methods
    virtual void myOutput() override;
};


#endif //PARSER_PARSER_H

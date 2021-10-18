//
// Created by unrelated on 2021/10/8.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "../Lexer/Lexer.h"
#include "../Exception/MyException.h"
#include "GramNode/CompUnit.h"

class Parser {
public:
    // public attributes

private:
    // private attributes
    std::vector<Token *> tokenList;
    GramNode *root;

public:
    // public methods
    Parser(std::vector<Token*>);

private:
    // private methods
};


#endif //PARSER_PARSER_H

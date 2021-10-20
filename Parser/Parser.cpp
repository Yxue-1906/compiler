//
// Created by unrelated on 2021/10/8.
//

#include "Parser.h"

Parser::Parser(std::vector<Token *> &tokenList) : tokenList(tokenList) {
    auto begin = tokenList.begin();
    std::vector<GramNode *> tmp;
    if (CompUnit::create(tmp, begin)) {
        root = tmp[0];
    } else throw new MyException();
}

void Parser::print() {
    this->myOutput();
}

void Parser::myOutput() {
    this->root->myOutput();
}
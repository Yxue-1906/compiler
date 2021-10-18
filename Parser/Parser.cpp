//
// Created by unrelated on 2021/10/8.
//

#include "Parser.h"

Parser::Parser(std::vector<Token *> tokenList) {
    this->tokenList = tokenList;
    auto begin = tokenList.begin();
    GramNode **node;
    if (CompUnit::create(node, begin)) {
        root = *node;
        root->myOutput();
    } else throw new MyException();
}
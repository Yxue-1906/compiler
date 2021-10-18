//
// Created by unrelated on 2021/10/8.
//

#include "Parser.h"

Parser::Parser(std::vector<Token *> tokenList) {
    this->tokenList = tokenList;
    auto begin = tokenList.begin();
    if (CompUnit::create(root, &begin))root->myOutput();
    else throw new MyException();
}
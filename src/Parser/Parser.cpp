//
// Created by unrelated on 2021/10/8.
//

#include "Parser.h"
#include "TestNode.h"

Parser::Parser(std::vector<TokenBase *> &tokenList) : tokenList(tokenList) {
    auto begin = tokenList.begin();
    std::vector<std::shared_ptr<GramNode>> tmp;
//    if (CompUnit::create(tmp, begin)) {
    if (CompUnit::create(tmp, begin)) {
        root = tmp[0];
    } else {
        std::cout << "stop at line:" << GramNode::nowLine << std::endl;
        throw MyException(-1, 'g');
    }
}

void Parser::print() {
    this->myOutput();
}

void Parser::myOutput() {
    this->root->myOutput();
}

std::shared_ptr<GramNode> Parser::getRoot() {
    return this->root;
}

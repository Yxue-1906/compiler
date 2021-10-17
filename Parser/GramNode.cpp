//
// Created by unrelated on 2021/10/17.
//

#include "GramNode.h"

void GramNode::setGramName(std::string gramName) {
    this->GramName = gramName;
}

void GramNode::setSons(std::vector<Token> sons) {
    this->sons = sons;
}

void GramNode::myOutput() {
    for (auto &i: sons) {
        i.myOutput();
    }
}
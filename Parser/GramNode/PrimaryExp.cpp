//
// Created by unrelated on 2021/10/18.
//

#include "PrimaryExp.h"
#include "../TokenNode.h"

PrimaryExp::PrimaryExp(std::vector<GramNode *> sons) {
    setGramName("PrimaryExp");
    setSons(std::move(sons));
}

bool PrimaryExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (TokenNode::create(son_ps, ite, Token::LPARENT)) {
        if ()
    }
}
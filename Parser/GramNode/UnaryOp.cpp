//
// Created by unrelated on 2021/10/18.
//

#include "UnaryOp.h"
#include "../TokenNode.h"

UnaryOp::UnaryOp(std::vector<GramNode *> sons) {
    setGramName("UnaryOp");
    setSons(std::move(sons));
}

bool UnaryOp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (TokenNode::create(son_ps, ite, Token::PLUS) ||
        TokenNode::create(son_ps, ite, Token::MINU) ||
        TokenNode::create(son_ps, ite, Token::NOT)) {
        toAdd.push_back(new UnaryOp(son_ps));
        ite_p = ite;
        return true;
    } else {
        return false;
    }
}
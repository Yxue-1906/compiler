//
// Created by unrelated on 2021/10/18.
//

#include "EqExp.h"
#include "RelExp.h"
#include "../TokenNode.h"

EqExp::EqExp(std::vector<GramNode *> sons) {
    setGramName("EqExp");
    setSons(std::move(sons));
}

bool EqExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!RelExp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::EQL) ||
           TokenNode::create(son_ps, ite, Token::NEQ);) {
        if (!RelExp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new EqExp(son_ps));
    return true;
}

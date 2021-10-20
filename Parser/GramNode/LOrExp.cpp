//
// Created by unrelated on 2021/10/18.
//

#include "LOrExp.h"
#include "LAndExp.h"
#include "../TokenNode.h"

LOrExp::LOrExp(std::vector<GramNode *> sons) {
    setGramName("LOrExp");
    setSons(std::move(sons));
}

bool LOrExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!LAndExp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::OR);) {
        if (!LAndExp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new LOrExp(son_ps));
    return true;
}

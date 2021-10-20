//
// Created by unrelated on 2021/10/18.
//

#include "LAndExp.h"
#include "EqExp.h"
#include "../TokenNode.h"

LAndExp::LAndExp(std::vector<GramNode *> sons): GramNode() {
    setGramName("LAndExp");
    setSons(std::move(sons));
}

bool LAndExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!EqExp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::AND);) {
        if (!EqExp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new LAndExp(son_ps));
    return true;
}

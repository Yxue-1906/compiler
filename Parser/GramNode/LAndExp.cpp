//
// Created by unrelated on 2021/10/18.
//

#include "LAndExp.h"
#include "EqExp.h"
#include "../TokenNode.h"

LAndExp::LAndExp(std::vector<GramNode *> sons) {
    setGramName("LAndExp");
    setSons(std::move(sons));
}

bool LAndExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!EqExp::create(nexNode, ite)) {
        return false;
    }
    for (; (**ite).isTypeOf(Token::AND);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!EqExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    ite_p = ite;
    toAdd = new LAndExp(son_ps);
    return true;
}

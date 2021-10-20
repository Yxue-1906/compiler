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
    GramNode *nexNode;
    if (!RelExp::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    for (; (**ite).isTypeOf(Token::EQL) ||
           (**ite).isTypeOf(Token::NEQ);) {
        son_ps.push_back(new TokenNode(**ite));
        if (!RelExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    ite_p = ite;
    toAdd = new EqExp(son_ps);
    return true;
}

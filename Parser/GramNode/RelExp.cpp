//
// Created by unrelated on 2021/10/18.
//

#include "RelExp.h"
#include "AddExp.h"
#include "../TokenNode.h"

RelExp::RelExp(std::vector<GramNode *> sons) {
    setGramName("RelExp");
    setSons(std::move(sons));
}

bool RelExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!AddExp::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    for (; (**ite).isTypeOf(Token::LEQ) ||
           (**ite).isTypeOf(Token::GEQ) ||
           (**ite).isTypeOf(Token::LSS) ||
           (**ite).isTypeOf(Token::GRE);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!AddExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    ite_p = ite;
    toAdd = new RelExp(son_ps);
    return true;
}

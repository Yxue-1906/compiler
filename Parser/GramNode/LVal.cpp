//
// Created by unrelated on 2021/10/20.
//

#include "LVal.h"
#include "Ident.h"
#include "../TokenNode.h"
#include "Exp.h"

LVal::LVal(std::vector<GramNode *> sons) {
    setGramName("LVal");
    setSons(std::move(sons));
}

bool LVal::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!Ident::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    for (; (**ite).isTypeOf(Token::LBRACK);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!Exp::create(nexNode, ite)) {
            return false;
        }
        if (!(**ite).isTypeOf(Token::RBRACK)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
    }
    ite_p = ite;
    toAdd = new LVal(son_ps);
    return true;
}
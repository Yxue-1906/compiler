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
    if (!Ident::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::LBRACK);) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::RBRACK)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new LVal(son_ps));
    return true;
}
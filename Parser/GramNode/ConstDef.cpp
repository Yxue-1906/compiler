//
// Created by unrelated on 2021/10/18.
//

#include "ConstDef.h"
#include "Ident.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "ConstInitVal.h"

ConstDef::ConstDef(std::vector<GramNode *> sons) {
    setGramName("ConstDef");
    setSons(std::move(sons));
}

bool ConstDef::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    GramNode *nexNode;
    std::vector<GramNode *> son_ps;
    if (!Ident::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    for (; (**ite).isTypeOf(Token::LBRACK);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!ConstExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        if (!(**ite).isTypeOf(Token::RBRACK)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
    }
    if (!(**ite).isTypeOf(Token::EQL)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if (!ConstInitVal::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    ite_p = ite;
    toAdd = new ConstDef(son_ps);
    return true;
}
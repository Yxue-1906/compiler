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
    std::vector<GramNode *> son_ps;
    if (!Ident::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::LBRACK);) {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::RBRACK)) {
            return false;
        }
    }
    if (!TokenNode::create(son_ps, ite, Token::EQL)) {
        return false;
    }
    if (!ConstInitVal::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new ConstDef(son_ps));
    return true;
}
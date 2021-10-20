//
// Created by unrelated on 2021/10/18.
//

#include "VarDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "ConstInitVal.h"

VarDef::VarDef(std::vector<GramNode *> sons) {
    setGramName("VarDef");
    setSons(std::move(sons));
}

bool VarDef::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::IDENFR)) {
        return false;
    }
    if (TokenNode::create(son_ps, ite, Token::LBRACK)) {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::RBRACK)) {
            return false;
        }
    }
    if (TokenNode::create(son_ps, ite, Token::EQL)) {
        if (!ConstInitVal::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new VarDef(son_ps));
    return true;
}
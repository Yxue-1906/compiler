//
// Created by unrelated on 2021/10/18.
//

#include "FuncDef.h"
#include "FuncType.h"
#include "../TokenNode.h"

FuncDef::FuncDef(std::vector<GramNode *> sons) {
    setGramName("FuncDef");
    setSons(std::move(sons));
}

bool FuncDef::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!FuncType::create(son_ps, ite)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, Token::IDENFR)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, Token::LPARENT)) {
        return false;
    }
    FuncFParams
}

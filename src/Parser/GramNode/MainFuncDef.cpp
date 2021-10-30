//
// Created by unrelated on 2021/10/18.
//

#include "MainFuncDef.h"
#include "../TokenNode.h"
#include "Block.h"

MainFuncDef::MainFuncDef(std::vector<GramNode *> sons) : GramNode() {
    setGramName("MainFuncDef");
    setSons(std::move(sons));
}

bool MainFuncDef::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!TokenNode::create(son_ps, ite, TokenBase::INTTK)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::MAINTK)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
        return false;
    }
    if (!Block::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new MainFuncDef(son_ps));
    return true;
}
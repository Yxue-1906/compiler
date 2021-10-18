//
// Created by unrelated on 2021/10/18.
//

#include "MainFuncDef.h"
#include "../TokenNode.h"
#include "Block.h"

MainFuncDef::MainFuncDef(std::vector<GramNode *> sons) {
    setGramName("MainFuncDef");
    setSons(std::move(sons));
}

bool MainFuncDef::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!(**ite).isTypeOf(Token::INTTK)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if (!(**ite).isTypeOf(Token::MAINTK)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if (!(**ite).isTypeOf(Token::LPARENT)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if (!(**ite).isTypeOf(Token::RPARENT)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if (!Block::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    ite_p = ite;
    toReturn = new MainFuncDef(son_ps);
    return true;
}
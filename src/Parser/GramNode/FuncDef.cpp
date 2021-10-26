//
// Created by unrelated on 2021/10/18.
//

#include "FuncDef.h"
#include "FuncType.h"
#include "../TokenNode.h"
#include "FuncFParams.h"
#include "Block.h"

FuncDef::FuncDef(std::vector<GramNode *> sons) : GramNode() {
    setGramName("FuncDef");
    setSons(std::move(sons));
}

/**
 * FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
 * @param toAdd
 * @param ite_p
 * @return
 */
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
    if (!Token::isTypeOf(ite, Token::RPARENT))
        if (!FuncFParams::create(son_ps, ite))
            return false;
    if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
        return false;
    }
    if (!Block::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new FuncDef(son_ps));
    return true;
}

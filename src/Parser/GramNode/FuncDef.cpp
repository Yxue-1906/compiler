//
// Created by unrelated on 2021/10/18.
//

#include "FuncDef.h"
#include "FuncType.h"
#include "../TokenNode.h"
#include "FuncFParams.h"
#include "Block.h"

FuncDef::FuncDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncDef");
    setSons(std::move(sons));
}

/**
 * FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!FuncType::create(son_ps, ite)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
        return false;
    }
    if (!TokenBase::isTypeOf(ite, TokenBase::RPARENT))
        if (!FuncFParams::create(son_ps, ite))
            return false;
    if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
        return false;
    }
    if (!Block::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<FuncDef> tmp_p;
    tmp_p.reset(new FuncDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}
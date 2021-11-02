//
// Created by unrelated on 2021/10/18.
//

#include "ConstDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "ConstInitVal.h"

ConstDef::ConstDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("ConstDef");
    setSons(std::move(sons));
}

/**
 * ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            return false;
        }
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::ASSIGN)) {
        return false;
    }
    if (!ConstInitVal::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<ConstDef> tmp_p;
    tmp_p.reset(new ConstDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}
//
// Created by unrelated on 2021/10/18.
//

#include "VarDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "InitVal.h"

VarDef::VarDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("VarDef");
    setSons(std::move(sons));
}

/**
 * VarDef -> Ident { '[' ConstExp ']' } |
 *           Ident { '[' ConstExp ']' } '=' InitVal
 * @param toAdd
 * @param ite_p
 * @return
 */
bool VarDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
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
    if (TokenNode::create(son_ps, ite, TokenBase::ASSIGN)) {
        if (!InitVal::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<VarDef> tmp_p;
    tmp_p.reset(new VarDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}
//
// Created by unrelated on 2021/10/20.
//

#include "LVal.h"
#include "../TokenNode.h"
#include "Exp.h"

LVal::LVal(std::vector<GramNode *> sons) : GramNode() {
    setGramName("LVal");
    setSons(std::move(sons));
}

/**
 * LVal → Ident {'[' Exp ']'}
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LVal::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new LVal(son_ps));
    return true;
}
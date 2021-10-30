//
// Created by unrelated on 2021/10/18.
//

#include "ConstInitVal.h"
#include "ConstExp.h"
#include "../TokenNode.h"

ConstInitVal::ConstInitVal(std::vector<GramNode *> sons) : GramNode() {
    setGramName("ConstInitVal");
    setSons(std::move(sons));
}

/**
 * ConstInitVal -> ConstExp |
 *                  '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstInitVal::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (TokenNode::create(son_ps, ite, TokenBase::LBRACE)) {
        if (TokenNode::create(son_ps, ite, TokenBase::RBRACE)) {
            toAdd.push_back(new ConstInitVal(son_ps));
            ite_p = ite;
            return true;
        }
        if (!ConstInitVal::create(son_ps, ite)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
            if (!ConstInitVal::create(son_ps, ite)) {
                return false;
            }
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACE)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new ConstInitVal(son_ps));
        return true;
    } else {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        toAdd.push_back(new ConstInitVal(son_ps));
        ite_p = ite;
        return true;
    }
}
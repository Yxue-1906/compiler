//
// Created by unrelated on 2021/10/18.
//

#include "ConstInitVal.h"
#include "ConstExp.h"
#include "../TokenNode.h"

ConstInitVal::ConstInitVal(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
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
bool ConstInitVal::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenNode::create(son_ps, ite, TokenBase::LBRACE)) {
        if (TokenNode::create(son_ps, ite, TokenBase::RBRACE)) {
            std::shared_ptr<GramNode> tmp_p;
            tmp_p.reset(new ConstInitVal(son_ps));
            toAdd.push_back(tmp_p);
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
        std::shared_ptr<ConstInitVal> tmp_p;
        tmp_p.reset(new ConstInitVal(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        std::shared_ptr<ConstInitVal> tmp_p;
        tmp_p.reset(new ConstInitVal(son_ps));
        toAdd.push_back(tmp_p);
        ite_p = ite;
        return true;
    }
}
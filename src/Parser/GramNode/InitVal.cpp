//
// Created by unrelated on 2021/10/20.
//

#include "InitVal.h"
#include "../TokenNode.h"
#include "Exp.h"

InitVal::InitVal(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("InitVal");
    setSons(std::move(sons));
}

/**
 * InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool InitVal::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenNode::create(son_ps, ite, TokenBase::LBRACE)) {
        if (!InitVal::create(son_ps, ite)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
            if (!InitVal::create(son_ps, ite)) {
                return false;
            }
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACE)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<InitVal> tmp_p;
        tmp_p.reset(new InitVal(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (Exp::create(son_ps, ite)) {
        ite_p = ite;
        std::shared_ptr<InitVal> tmp_p;
        tmp_p.reset(new InitVal(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }
    return false;
}
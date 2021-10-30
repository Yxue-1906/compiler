//
// Created by unrelated on 2021/10/18.
//

#include "EqExp.h"
#include "RelExp.h"
#include "../TokenNode.h"

EqExp::EqExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("EqExp");
    setSons(std::move(sons));
}

/**
 * EqExp -> RelExp | EqExp ('==' | '!=') RelExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool EqExp::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    std::swap(toAdd, son_ps);
    if (!RelExp::create(son_ps, ite)) {
        return false;
    }
    toAdd.push_back(new EqExp(son_ps));
    if (TokenNode::create(toAdd, ite, TokenBase::EQL) ||
        TokenNode::create(toAdd, ite, TokenBase::NEQ)) {
        if (!EqExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

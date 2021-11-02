//
// Created by unrelated on 2021/10/18.
//

#include "RelExp.h"
#include "AddExp.h"
#include "../TokenNode.h"

RelExp::RelExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("RelExp");
    setSons(std::move(sons));
}

/**
 * RelExp -> AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool RelExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    std::swap(toAdd, son_ps);
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<RelExp> tmp_p;
    tmp_p.reset(new RelExp(son_ps));
    toAdd.push_back(tmp_p);
    for (; TokenNode::create(toAdd, ite, TokenBase::LEQ) ||
           TokenNode::create(toAdd, ite, TokenBase::GEQ) ||
           TokenNode::create(toAdd, ite, TokenBase::LSS) ||
           TokenNode::create(toAdd, ite, TokenBase::GRE);) {
        if (!RelExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}
//
// Created by unrelated on 2021/10/18.
//

#include "EqExp.h"
#include "RelExp.h"
#include "../TokenNode.h"

EqExp::EqExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("EqExp");
    setSons(std::move(sons));
}

/**
 * EqExp -> RelExp | EqExp ('==' | '!=') RelExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool EqExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!RelExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<EqExp> eqExp_p;
    eqExp_p.reset(new EqExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(eqExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::EQL) ||
            TokenNode::create(tmp, ite, TokenBase::NEQ)) {
            if (!RelExp::create(tmp, ite))
                return false;
            eqExp_p.reset(new EqExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(eqExp_p);
    return true;
}

bool EqExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

//
// Created by unrelated on 2021/10/18.
//

#include "LAndExp.h"
#include "EqExp.h"
#include "../TokenNode.h"

LAndExp::LAndExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("LAndExp");
    setSons(std::move(sons));
}

/**
 * LAndExp -> EqExp | LAndExp '&&' EqExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LAndExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    std::swap(toAdd, son_ps);
    if (!EqExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<LAndExp> tmp_p;
    tmp_p.reset(new LAndExp(son_ps));
    toAdd.push_back(tmp_p);
    if (TokenNode::create(toAdd, ite, TokenBase::AND)) {
        if (!LAndExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

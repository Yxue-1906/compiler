//
// Created by unrelated on 2021/10/18.
//

#include "LAndExp.h"
#include "EqExp.h"
#include "../TokenNode.h"

LAndExp::LAndExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("LAndExp");
    setSons(std::move(sons));
}

/**
 * LAndExp -> EqExp | LAndExp '&&' EqExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LAndExp::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    std::swap(toAdd, son_ps);
    if (!EqExp::create(son_ps, ite)) {
        return false;
    }
    toAdd.push_back(new LAndExp(son_ps));
    if (TokenNode::create(toAdd, ite, TokenBase::AND)) {
        if (!LAndExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

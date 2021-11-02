//
// Created by unrelated on 2021/10/18.
//

#include "LOrExp.h"
#include "LAndExp.h"
#include "../TokenNode.h"

LOrExp::LOrExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("LOrExp");
    setSons(std::move(sons));
}

/**
 * LOrExp -> LAndExp | LOrExp '||' LAndExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LOrExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    std::swap(toAdd, son_ps);
    if (!LAndExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<LOrExp> tmp_p;
    tmp_p.reset(new LOrExp(son_ps));
    toAdd.push_back(tmp_p);
    if (TokenNode::create(toAdd, ite, TokenBase::OR)) {
        if (!LOrExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

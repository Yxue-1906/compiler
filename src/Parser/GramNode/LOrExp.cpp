//
// Created by unrelated on 2021/10/18.
//

#include "LOrExp.h"
#include "LAndExp.h"
#include "../TokenNode.h"

LOrExp::LOrExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("LOrExp");
    setSons(std::move(sons));
}

/**
 * LOrExp -> LAndExp | LOrExp '||' LAndExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LOrExp::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    std::swap(toAdd, son_ps);
    if (!LAndExp::create(son_ps, ite)) {
        return false;
    }
    toAdd.push_back(new LOrExp(son_ps));
    if (TokenNode::create(toAdd, ite, TokenBase::OR)) {
        if (!LOrExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

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
    if (!EqExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<LAndExp> lAndExp_p;
    lAndExp_p.reset(new LAndExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(lAndExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::AND)) {
            if (!EqExp::create(tmp, ite))
                return false;
            lAndExp_p.reset(new LAndExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(lAndExp_p);
    return true;
}

bool LAndExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

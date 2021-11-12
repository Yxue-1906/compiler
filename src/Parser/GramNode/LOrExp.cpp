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
    if (!LAndExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<LOrExp> lOrExp_p;
    lOrExp_p.reset(new LOrExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(lOrExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::OR)) {
            if (!LAndExp::create(tmp, ite))
                return false;
            lOrExp_p.reset(new LOrExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(lOrExp_p);
    return true;
}

bool LOrExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

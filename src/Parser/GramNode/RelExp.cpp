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
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<RelExp> relExp_p;
    relExp_p.reset(new RelExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(relExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::LEQ) ||
            TokenNode::create(tmp, ite, TokenBase::GEQ) ||
            TokenNode::create(tmp, ite, TokenBase::LSS) ||
            TokenNode::create(tmp, ite, TokenBase::GRE)) {
            if (!AddExp::create(tmp, ite))
                return false;
            relExp_p.reset(new RelExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(relExp_p);
    return true;
}

bool RelExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

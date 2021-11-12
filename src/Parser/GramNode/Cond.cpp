//
// Created by unrelated on 2021/10/18.
//

#include "Cond.h"
#include "LOrExp.h"

Cond::Cond(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("Cond");
    setSons(std::move(sons));
}

/**
 * Cond -> LOrExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Cond::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!LOrExp::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<Cond> tmp_p;
    tmp_p.reset(new Cond(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool Cond::checkValid() {
    auto lOrExp_p = std::dynamic_pointer_cast<LOrExp>(sons.back());
    return lOrExp_p->checkValid();
}

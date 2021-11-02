//
// Created by unrelated on 2021/10/18.
//

#include "ConstExp.h"
#include "AddExp.h"

ConstExp::ConstExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("ConstExp");
    setSons(std::move(sons));
}

/**
 * ConstExp -> AddExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<ConstExp> tmp_p;
    tmp_p.reset(new ConstExp(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}
//
// Created by unrelated on 2021/10/18.
//

#include "ConstExp.h"
#include "AddExp.h"

ConstExp::ConstExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("ConstExp");
    setSons(std::move(sons));
}

/**
 * ConstExp -> AddExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new ConstExp(son_ps));
    return true;
}
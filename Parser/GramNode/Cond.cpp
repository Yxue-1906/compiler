//
// Created by unrelated on 2021/10/18.
//

#include "Cond.h"
#include "LOrExp.h"

Cond::Cond(std::vector<GramNode *> sons) {
    setGramName("Cond");
    setSons(std::move(sons));
}

bool Cond::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!LOrExp::create(nexNode, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd = new Cond(son_ps);
    return true;
}

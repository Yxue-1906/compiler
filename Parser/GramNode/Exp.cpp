//
// Created by unrelated on 2021/10/18.
//

#include "Exp.h"
#include "AddExp.h"

Exp::Exp(std::vector<GramNode *> sons) {
    setGramName("Exp");
    setSons(std::move(sons));
}

bool Exp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new Exp(son_ps));
    return true;
}
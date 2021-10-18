//
// Created by unrelated on 2021/10/18.
//

#include "Exp.h"
#include "AddExp.h"

Exp::Exp(std::vector<GramNode *> sons) {
    setGramName("Exp");
    setSons(std::move(sons));
}

bool Exp::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!AddExp::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    toReturn = new Exp(son_ps);
    ite_p = ite;
    return true;
}
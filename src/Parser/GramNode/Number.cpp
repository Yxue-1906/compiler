//
// Created by unrelated on 2021/10/20.
//

#include "Number.h"
#include "../TokenNode.h"

Number::Number(std::vector<GramNode *> sons) : GramNode() {
    setGramName("Number");
    setSons(std::move(sons));
}

bool Number::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::INTCON)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new Number(son_ps));
    return true;
}
//
// Created by unrelated on 2021/10/18.
//

#include "UnaryExp.h"
#include "../TokenNode.h"

UnaryExp::UnaryExp(std::vector<GramNode *> sons) {
    setGramName("UnaryExp");
    setSons(std::move(sons));
}

bool UnaryExp::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if()
}
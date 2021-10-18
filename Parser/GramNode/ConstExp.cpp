//
// Created by unrelated on 2021/10/18.
//

#include "ConstExp.h"

ConstExp::ConstExp(std::vector<GramNode *> sons) {
    setGramName("ConstExp");
    setSons(std::move(sons));
}

bool ConstExp::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if(!)
}
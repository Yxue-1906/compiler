//
// Created by unrelated on 2021/10/17.
//

#include "CompUnit.h"

CompUnit::CompUnit(std::vector<GramNode> sons) {
    setGramName("CompUnit");
    setSons(std::move(sons));
}

bool CompUnit::create(GramNode &toReturn, std::vector<Token *>::iterator *ite_p) {
    auto ite = *ite_p;
    std::vector<Token> sons;
    for (;;)
    //todo
}

//
// Created by unrelated on 2021/10/18.
//

#include "Decl.h"

Decl::Decl(std::vector<GramNode> sons) {
    setGramName("Decl");
    setSons(std::move(sons));
}

bool Decl::create(GramNode *toReturn, std::vector<Token *>::iterator *ite_p) {
    auto ite = *ite_p;
    std::vector<Token> sons;

}
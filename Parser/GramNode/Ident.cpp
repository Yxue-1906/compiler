//
// Created by unrelated on 2021/10/18.
//

#include "Ident.h"
#include "../TokenNode.h"

Ident::Ident(std::vector<GramNode *> sons) {
    setGramName("Ident");
    setSons(std::move(sons));
}

bool Ident::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::IDENFR))
        return false;
    ite_p = ite;
    toAdd .push_back(new Ident(son_ps)) ;
    return true;
}
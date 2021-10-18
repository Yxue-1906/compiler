//
// Created by unrelated on 2021/10/18.
//

#include "ConstDef.h"
#include "Ident.h"
#include "../TokenNode.h"

ConstDef::ConstDef(std::vector<GramNode *> sons) {
    setGramName("ConstDef");
    setSons(std::move(sons));
}

bool ConstDef::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    GramNode *nexNode;
    std::vector<GramNode *> son_ps;
    if (!Ident::create(nexNode, ite)) {
        delete nexNode;
        return false;
    }
    son_ps.push_back(nexNode);
    //
    for (; (**ite).isTypeOf(Token::LBRACK);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;

    }
}
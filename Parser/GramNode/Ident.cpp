//
// Created by unrelated on 2021/10/18.
//

#include "Ident.h"
#include "../TokenNode.h"

Ident::Ident(std::vector<GramNode *> sons) {
    setGramName("Ident");
    setSons(std::move(sons));
}

bool Ident::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!(**ite).isTypeOf(Token::IDENFR))
        return false;
    son_ps.push_back(new TokenNode(**ite));
    toReturn = new Ident(son_ps);
    ite_p = ite;
    return true;
}
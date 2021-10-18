//
// Created by unrelated on 2021/10/18.
//

#include "BType.h"


BType::BType(std::vector<GramNode *> sons) {
    setGramName("BType");
    setSons(std::move(sons));
}

bool BType::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!(**ite).isTypeOf(Token::INTTK))
        return false;
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    toReturn = new BType(son_ps);
    ite_p = ite;
    return true;
}
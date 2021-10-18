//
// Created by unrelated on 2021/10/18.
//

#include "LOrExp.h"
#include "LAndExp.h"
#include "../TokenNode.h"

LOrExp::LOrExp(std::vector<GramNode *> sons) {
    setGramName("LOrExp");
    setSons(std::move(sons));
}

bool LOrExp::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!LAndExp::create(nexNode, ite)) {
        return false;
    }
    for (; (**ite).isTypeOf(Token::OR);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!LAndExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    ite_p = ite;
    toReturn = new LOrExp(son_ps);
    return true;
}

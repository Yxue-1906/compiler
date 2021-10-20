//
// Created by unrelated on 2021/10/18.
//

#include "AddExp.h"
#include "MulExp.h"
#include "../TokenNode.h"

AddExp::AddExp(std::vector<GramNode *> sons) {
    setGramName("AddExp");
    setSons(std::move(sons));
}

bool AddExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!MulExp::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    for (; (**ite).isTypeOf(Token::PLUS) || (**ite).isTypeOf(Token::MINU);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!MulExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    ite_p = ite;
    toAdd.push_back(new AddExp(son_ps));
    return true;
}
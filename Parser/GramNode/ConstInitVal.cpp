//
// Created by unrelated on 2021/10/18.
//

#include "ConstInitVal.h"
#include "ConstExp.h"
#include "../TokenNode.h"

ConstInitVal::ConstInitVal(std::vector<GramNode *> sons) {
    setGramName("ConstInitVal");
    setSons(std::move(sons));
}

bool ConstInitVal::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if ((**ite).isTypeOf(Token::LBRACE)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if ((**ite).isTypeOf(Token::RBRACE)) {
            son_ps.push_back(new TokenNode(**ite));
            ++ite;
            toReturn = new ConstInitVal(son_ps);
            ite_p = ite;
            return true;
        }
        if (!ConstInitVal::create(nexNode, ite)) {
            return false;
        }
        for (; (**ite).isTypeOf(Token::SEMICN);) {
            son_ps.push_back(new TokenNode(**ite));
            ++ite;
            if (!ConstInitVal::create(nexNode, ite)) {
                return false;
            }
            son_ps.push_back(nexNode);
        }
        if (!(**ite).isTypeOf(Token::RBRACE)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        ite_p = ite;
        toReturn = new ConstInitVal(son_ps);
        return true;
    } else {
        if (!ConstExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        toReturn = new ConstInitVal(son_ps);
        ite_p = ite;
        return true;
    }
}
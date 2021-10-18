//
// Created by unrelated on 2021/10/18.
//

#include "ConstDecl.h"
#include "../../Lexer/Token/CONSTTK.h"
#include "../TokenNode.h"
#include "BType.h"
#include "ConstDef.h"


ConstDecl::ConstDecl(std::vector<GramNode *> sons) {
    setGramName("ConstDecl");
    setSons(std::move(sons));
}

bool ConstDecl::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    GramNode *nexNode;
    std::vector<GramNode *> son_ps;
    if (!(**ite).isTypeOf(Token::CONSTTK)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ite++;
    if (!BType::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    if (!ConstDef::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    for (; (**ite).isTypeOf(Token::COMMA);) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!ConstDef::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    if (!(**ite).isTypeOf(Token::SEMICN)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    toReturn = new ConstDecl(son_ps);
    return true;
}
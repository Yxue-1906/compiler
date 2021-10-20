//
// Created by unrelated on 2021/10/18.
//

#include "ConstDecl.h"
#include "../../Lexer/Token/CONSTTK.h"
#include "../TokenNode.h"
#include "BType.h"
#include "ConstDef.h"


ConstDecl::ConstDecl(std::vector<GramNode *> sons) : GramNode() {
    setGramName("ConstDecl");
    setSons(std::move(sons));
}

/**
 * ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstDecl::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::CONSTTK)) {
        return false;
    }
    if (!BType::create(son_ps, ite)) {
        return false;
    }
    if (!ConstDef::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::COMMA);) {
        if (!ConstDef::create(son_ps, ite)) {
            return false;
        }
    }
    if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new ConstDecl(son_ps));
    return true;
}
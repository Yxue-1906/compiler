//
// Created by unrelated on 2021/10/18.
//

#include "VarDecl.h"
#include "BType.h"
#include "VarDef.h"

VarDecl::VarDecl(std::vector<GramNode *> sons) {
    setGramName("VarDecl");
    setSons(std::move(sons));
}

/**
 * VarDecl → BType VarDef { ',' VarDef } ';'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool VarDecl::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!BType::create(son_ps, ite)) {
        return false;
    }
    if (!VarDef::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::COMMA);) {
        if (!VarDef::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new VarDecl(son_ps));
    return true;
}
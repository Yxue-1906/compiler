//
// Created by unrelated on 2021/10/18.
//

#include "ConstDecl.h"
#include "../../Lexer/Token/CONSTTK.h"
#include "../TokenNode.h"
#include "BType.h"
#include "ConstDef.h"


ConstDecl::ConstDecl(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("ConstDecl");
    setSons(std::move(sons));
}

/**
 * ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstDecl::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::CONSTTK)) {
        return false;
    }
    if (!BType::create(son_ps, ite)) {
        return false;
    }
    if (!ConstDef::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
        if (!ConstDef::create(son_ps, ite)) {
            return false;
        }
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<ConstDecl> tmp_p;
    tmp_p.reset(new ConstDecl(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool ConstDecl::checkValid() {
    bool toReturn = true;
    auto ite = this->sons.begin();
    ite += 2;
    for (; ite != sons.end(); ite += 2) {
        toReturn &= (*ite)->checkValid();
    }
    return toReturn;
}

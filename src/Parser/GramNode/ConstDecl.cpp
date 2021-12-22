//
// Created by unrelated on 2021/10/18.
//

#include "ConstDecl.h"
#include "../../Lexer/Token/CONSTTK.h"
#include "../TokenNode.h"
#include "BType.h"
#include "ConstDef.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"
#include "../../Exception/MyException/MissingSemicolonException.h"


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
        ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
    }
    ite_p = ite;
    std::shared_ptr<ConstDecl> tmp_p;
    tmp_p.reset(new ConstDecl(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool ConstDecl::checkValid() {
    bool toReturn = true;
    for (auto &i: this->sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

std::string ConstDecl::toMidCode() {
    auto ite = this->sons.begin() + 2;
    auto constDef_p = std::dynamic_pointer_cast<ConstDef>(*ite);
    for (; constDef_p && (ite < this->sons.end());
           ite += 2, constDef_p = std::dynamic_pointer_cast<ConstDef>(*ite)) {
        constDef_p->toMidCode();
    }
    return "";
}

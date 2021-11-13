//
// Created by unrelated on 2021/10/18.
//

#include "VarDecl.h"
#include "BType.h"
#include "VarDef.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"
#include "../../Lexer/Token/LBRACK.h"
#include "../../Exception/MyException/MissingSemicolonException.h"

VarDecl::VarDecl(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("VarDecl");
    setSons(std::move(sons));
}

/**
 * VarDecl → BType VarDef { ',' VarDef } ';'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool VarDecl::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!BType::create(son_ps, ite)) {
        return false;
    }
    if (!VarDef::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
        if (!VarDef::create(son_ps, ite)) {
            return false;
        }
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
        ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
    }
    ite_p = ite;
    std::shared_ptr<VarDecl> tmp_p;
    tmp_p.reset(new VarDecl(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool VarDecl::checkValid() {
    bool toReturn = true;
    for (auto &i: this->sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}


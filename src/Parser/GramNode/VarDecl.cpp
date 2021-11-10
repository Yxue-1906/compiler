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

bool VarDecl::addIdent() {
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    std::string name = *ident_p->getValue_p();
    ++ite;
    int dimension = 0;
    for (; ite != sons.end(); ++ite) {
        auto errorNode = std::dynamic_pointer_cast<ErrorNode>(*ite);
        if (errorNode) {
            return false;
        }
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lbrack_p = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lbrack_p) {
                dimension++;
            }
        }
    }
    try {
        if (!GramNode::getNowTable()->addIdent(name, std::make_shared<IdentInfo>(false, dimension))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (DupIdentException &e) {
        e.myOutput();
        return false;
    }
    return true;
}


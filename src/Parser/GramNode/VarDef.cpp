//
// Created by unrelated on 2021/10/18.
//

#include "VarDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "InitVal.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"
#include "../../Lexer/Token/LBRACK.h"

VarDef::VarDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("VarDef");
    setSons(std::move(sons));
}

/**
 * VarDef -> Ident { '[' ConstExp ']' } |
 *           Ident { '[' ConstExp ']' } '=' InitVal
 * @param toAdd
 * @param ite_p
 * @return
 */
bool VarDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            return false;
        }
    }
    if (TokenNode::create(son_ps, ite, TokenBase::ASSIGN)) {
        if (!InitVal::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<VarDef> tmp_p;
    tmp_p.reset(new VarDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool VarDef::checkValid() {
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    int dimension = 0;
    ++ite;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lb = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lb)
                dimension++;
        } else if (!(*ite)->checkValid()) {
            return false;
        }
    }
    try {
        if (!GramNode::getNowTable()->addIdent(*ident_p->getValue_p(), std::make_shared<IdentInfo>(false, dimension))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    return true;
}

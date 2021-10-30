//
// Created by unrelated on 2021/10/18.
//

#include "UnaryExp.h"
#include "../TokenNode.h"
#include "FuncRParams.h"
#include "PrimaryExp.h"
#include "UnaryOp.h"

UnaryExp::UnaryExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("UnaryExp");
    setSons(std::move(sons));
}

/**
 * UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')'| UnaryOp UnaryExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool UnaryExp::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (TokenBase::isTypeOf(ite, TokenBase::PLUS) ||
        TokenBase::isTypeOf(ite, TokenBase::MINU) ||
        TokenBase::isTypeOf(ite, TokenBase::NOT)) {
        if (!UnaryOp::create(son_ps, ite)) {
            return false;
        }
        if (!UnaryExp::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new UnaryExp(son_ps));
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::IDENFR) &&
               TokenBase::isTypeOf(ite + 1, TokenBase::LPARENT)) {
        TokenNode::create(son_ps, ite, TokenBase::IDENFR);
        TokenNode::create(son_ps, ite, TokenBase::LPARENT);
        if (!TokenBase::isTypeOf(ite, TokenBase::RPARENT))
            if (!FuncRParams::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new UnaryExp(son_ps));
        return true;
    } else if (PrimaryExp::create(son_ps, ite)) {
        ite_p = ite;
        toAdd.push_back(new UnaryExp(son_ps));
        return true;
    }
    return false;
}
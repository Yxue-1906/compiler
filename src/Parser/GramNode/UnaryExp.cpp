//
// Created by unrelated on 2021/10/18.
//

#include "UnaryExp.h"
#include "../TokenNode.h"
#include "FuncRParams.h"
#include "PrimaryExp.h"
#include "UnaryOp.h"

UnaryExp::UnaryExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("UnaryExp");
    setSons(std::move(sons));
}

/**
 * UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')'| UnaryOp UnaryExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool UnaryExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
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
        std::shared_ptr<UnaryExp> tmp_p;
        tmp_p.reset(new UnaryExp(son_ps));
        toAdd.push_back(tmp_p);
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
        std::shared_ptr<UnaryExp> tmp_p;
        tmp_p.reset(new UnaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (PrimaryExp::create(son_ps, ite)) {
        ite_p = ite;
        std::shared_ptr<UnaryExp> tmp_p;
        tmp_p.reset(new UnaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }
    return false;
}
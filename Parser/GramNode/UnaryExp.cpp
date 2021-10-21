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
bool UnaryExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (Token::isTypeOf(ite, Token::PLUS) ||
        Token::isTypeOf(ite, Token::MINU) ||
        Token::isTypeOf(ite, Token::NOT)) {
        if (!UnaryOp::create(son_ps, ite)) {
            return false;
        }
        if (!UnaryExp::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new UnaryExp(son_ps));
        return true;
    } else if (Token::isTypeOf(ite, Token::IDENFR) &&
               Token::isTypeOf(ite + 1, Token::LPARENT)) {
        TokenNode::create(son_ps, ite, Token::IDENFR);
        TokenNode::create(son_ps, ite, Token::LPARENT);
        FuncRParams::create(son_ps, ite);
        if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
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
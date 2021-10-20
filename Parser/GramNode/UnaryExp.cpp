//
// Created by unrelated on 2021/10/18.
//

#include "UnaryExp.h"
#include "../TokenNode.h"
#include "FuncFParams.h"
#include "PrimaryExp.h"

UnaryExp::UnaryExp(std::vector<GramNode *> sons) {
    setGramName("UnaryExp");
    setSons(std::move(sons));
}

/**
 * UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool UnaryExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if ((**(ite + 2)).isTypeOf(Token::LPARENT)) {
        if (!TokenNode::create(son_ps, ite, Token::IDENFR)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::LPARENT)) {
            return false;
        }
        FuncFParams::create(son_ps, ite);
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
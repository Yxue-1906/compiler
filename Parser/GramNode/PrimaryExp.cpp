//
// Created by unrelated on 2021/10/18.
//

#include "PrimaryExp.h"
#include "../TokenNode.h"
#include "Exp.h"
#include "Number.h"
#include "LVal.h"

PrimaryExp::PrimaryExp(std::vector<GramNode *> sons) : GramNode(){
    setGramName("PrimaryExp");
    setSons(std::move(sons));
}

/**
 * PrimaryExp → '(' Exp ')' | LVal | Number
 * @param toAdd
 * @param ite_p
 * @return
 */
bool PrimaryExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (TokenNode::create(son_ps, ite, Token::LPARENT)) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new PrimaryExp(son_ps));
        return true;
    } else if (Number::create(son_ps, ite) ||
               LVal::create(son_ps, ite)) {
        ite_p = ite;
        toAdd.push_back(new PrimaryExp(son_ps));
        return true;
    }
    return false;
}
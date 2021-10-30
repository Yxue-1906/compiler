//
// Created by unrelated on 2021/10/18.
//

#include "PrimaryExp.h"
#include "../TokenNode.h"
#include "Exp.h"
#include "Number.h"
#include "LVal.h"

PrimaryExp::PrimaryExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("PrimaryExp");
    setSons(std::move(sons));
}

/**
 * PrimaryExp → '(' Exp ')' | LVal | Number
 * @param toAdd
 * @param ite_p
 * @return
 */
bool PrimaryExp::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    auto detectNumber = [&ite]() -> bool {
        if (TokenBase::isTypeOf(ite, TokenBase::INTCON))
            return true;
        return false;
    };
    if (TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new PrimaryExp(son_ps));
        return true;
    } else if (detectNumber()) {
        Number::create(son_ps, ite);
        ite_p = ite;
        toAdd.push_back(new PrimaryExp(son_ps));
        return true;
    } else {
        if (!LVal::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new PrimaryExp(son_ps));
        return true;
    }
}
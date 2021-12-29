//
// Created by unrelated on 2021/10/18.
//

#include "EqExp.h"
#include "RelExp.h"
#include "../TokenNode.h"
#include "../../VM/PCode/EQ.h"
#include "../../VM/PCode/NEQ.h"

EqExp::EqExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("EqExp");
    setSons(std::move(sons));
}

/**
 * EqExp -> RelExp | EqExp ('==' | '!=') RelExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool EqExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!RelExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<EqExp> eqExp_p;
    eqExp_p.reset(new EqExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(eqExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::EQL) ||
            TokenNode::create(tmp, ite, TokenBase::NEQ)) {
            if (!RelExp::create(tmp, ite))
                return false;
            eqExp_p.reset(new EqExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(eqExp_p);
    return true;
}

bool EqExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> EqExp::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    if (sons.size() > 1) {
        auto eqExp_p = std::dynamic_pointer_cast<EqExp>(sons[0]);
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto reqExp_p = std::dynamic_pointer_cast<RelExp>(sons[2]);
        auto tmpVar1_p = eqExp_p->toMidCode()[0];
        auto tmpVar2_p = reqExp_p->toMidCode()[0];
        auto tmpVar_p = symTableGenCode.getNewTmpVarName();
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::EQL) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::EQ>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::NEQ>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        }
        toReturn.push_back(tmpVar_p);
    } else {
        auto reqExp = std::dynamic_pointer_cast<RelExp>(sons[0]);
        toReturn = (reqExp->toMidCode());
    }
    return toReturn;
}

//
// Created by unrelated on 2021/10/18.
//

#include "RelExp.h"
#include "AddExp.h"
#include "../TokenNode.h"
#include "../../VM/PCode/LSS.h"
#include "../../VM/PCode/LEQ.h"
#include "../../VM/PCode/GEQ.h"
#include "../../VM/PCode/GRE.h"

RelExp::RelExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("RelExp");
    setSons(std::move(sons));
}

/**
 * RelExp -> AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool RelExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<RelExp> relExp_p;
    relExp_p.reset(new RelExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(relExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::LEQ) ||
            TokenNode::create(tmp, ite, TokenBase::GEQ) ||
            TokenNode::create(tmp, ite, TokenBase::LSS) ||
            TokenNode::create(tmp, ite, TokenBase::GRE)) {
            if (!AddExp::create(tmp, ite))
                return false;
            relExp_p.reset(new RelExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(relExp_p);
    return true;
}

bool RelExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> RelExp::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    if (sons.size() > 1) {
        auto relExp_p = std::dynamic_pointer_cast<RelExp>(sons[0]);
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto addExp_p = std::dynamic_pointer_cast<AddExp>(sons[2]);
        auto tmpVar1_p = relExp_p->toMidCode()[0];
        auto tmpVar2_p = addExp_p->toMidCode()[0];
        auto tmpVar_p = symTableGenCode.getNewTmpVarName();
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::LSS) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::LSS>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::GRE) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::GRE>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::LEQ) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::LEQ>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::GEQ>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        }
        toReturn.push_back(tmpVar_p);
    } else {
        auto addExp_p = std::dynamic_pointer_cast<AddExp>(sons[0]);
        toReturn = addExp_p->toMidCode();
    }
    return toReturn;
}

//
// Created by unrelated on 2021/10/18.
//

#include "LAndExp.h"
#include "EqExp.h"
#include "../TokenNode.h"
#include "../../VM/PCode/AND.h"
#include "../../VM/PCode/BRF.h"
#include "../../VM/PCode/LOD.h"
#include "../../VM/PCode/ADD.h"

LAndExp::LAndExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("LAndExp");
    setSons(std::move(sons));
}

/**
 * LAndExp -> EqExp | LAndExp '&&' EqExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LAndExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!EqExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<LAndExp> lAndExp_p;
    lAndExp_p.reset(new LAndExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(lAndExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::AND)) {
            if (!EqExp::create(tmp, ite))
                return false;
            lAndExp_p.reset(new LAndExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(lAndExp_p);
    return true;
}

bool LAndExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> LAndExp::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    if (sons.size() > 1) {
        auto lAndExp_p = std::dynamic_pointer_cast<LAndExp>(sons[0]);
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto eqExp_p = std::dynamic_pointer_cast<EqExp>(sons[2]);
        auto tmpVar1_p = lAndExp_p->toMidCode()[0];
        auto tmpVar2_p = eqExp_p->toMidCode()[0];
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::AND>(*tmpVar1_p, *tmpVar2_p, *tmpVar1_p));
        andLabels->push_back(MidCodeSequence.size());
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::BRF>(*tmpVar1_p));
        toReturn.push_back(tmpVar1_p);
    } else {
        auto eqExp_p = std::dynamic_pointer_cast<EqExp>(sons[0]);
        auto tmpVars_p = eqExp_p->toMidCode();
        auto tmpVar_p = symTableGenCode.getNewTmpVarName();
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::ADD>(*tmpVars_p[0], "0", *tmpVar_p));
        andLabels->push_back(MidCodeSequence.size());
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::BRF>(*tmpVar_p));
        toReturn.push_back(tmpVar_p);
    }
    return toReturn;
}

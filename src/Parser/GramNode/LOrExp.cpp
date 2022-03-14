//
// Created by unrelated on 2021/10/18.
//

#include "LOrExp.h"
#include "LAndExp.h"
#include "../TokenNode.h"
#include "../../VM/PCode/BRT.h"
#include "../../VM/PCode/BRF.h"
#include "../../VM/PCode/OR.h"

LOrExp::LOrExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("LOrExp");
    setSons(std::move(sons));
}

/**
 * LOrExp -> LAndExp | LOrExp '||' LAndExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LOrExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!LAndExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<LOrExp> lOrExp_p;
    lOrExp_p.reset(new LOrExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(lOrExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::OR)) {
            if (!LAndExp::create(tmp, ite))
                return false;
            lOrExp_p.reset(new LOrExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(lOrExp_p);
    return true;
}

bool LOrExp::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> LOrExp::toMidCode() {
    //todo:
    std::vector<std::shared_ptr<std::string>> toReturn;
    if (sons.size() > 1) {
        auto lOrExp_p = std::dynamic_pointer_cast<LOrExp>(sons[0]);
        auto tokenNode_p = std::dynamic_pointer_cast<TokenBase>(sons[1]);
        auto lAndExp_p = std::dynamic_pointer_cast<LAndExp>(sons[2]);
        auto tmpVar1_p = lOrExp_p->toMidCode()[0];
        auto formerAndLabels = andLabels;
        andLabels = std::make_shared<std::vector<int>>();
        auto tmpVar2_p = lAndExp_p->toMidCode()[0];
        std::string nowLabel = "$" + std::to_string(nowLabelCount++);
        for (int i: *andLabels) {
            auto brf_p = std::dynamic_pointer_cast<INTERPRETER::BRF>(MidCodeSequence[i]);
            if (brf_p) {
                brf_p->setLabel(nowLabel);
            } else {
                //should not run to here!
                int tmp;
                std::cout << "error! get null ptr" << std::endl;
//                std::cin >> tmp;
            }
        }
        andLabels = formerAndLabels;
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::OR>(*tmpVar1_p, *tmpVar2_p, *tmpVar1_p));
        orLabels->push_back(MidCodeSequence.size());
        labels.emplace(nowLabel, MidCodeSequence.size());
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::BRT>(*tmpVar1_p));
        toReturn.push_back(tmpVar1_p);
    } else {
        auto formerAndLabels = andLabels;
        andLabels = std::make_shared<std::vector<int>>();
        auto lAndExp_p = std::dynamic_pointer_cast<LAndExp>(sons[0]);
        toReturn = lAndExp_p->toMidCode();
        orLabels->push_back(MidCodeSequence.size());
        std::string nowLabel = "$" + std::to_string(nowLabelCount++);
        for (int i: *andLabels) {
            auto brf_p = std::dynamic_pointer_cast<INTERPRETER::BRF>(MidCodeSequence[i]);
            if (brf_p) {
                brf_p->setLabel(nowLabel);
            } else {
                //should not run to here!
                int tmp;
                std::cout << "error! get null ptr" << std::endl;
//                std::cin >> tmp;
            }
        }
        andLabels = formerAndLabels;
        labels.emplace(nowLabel, MidCodeSequence.size());
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::BRT>(*toReturn[0]));
    }
    return toReturn;
}

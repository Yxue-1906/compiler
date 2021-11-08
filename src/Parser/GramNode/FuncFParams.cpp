//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParams.h"
#include "FuncFParam.h"
#include "../TokenNode.h"

FuncFParams::FuncFParams(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncFParams");
    setSons(std::move(sons));
}

/**
 * FuncFParams -> FuncFParam { ',' FuncFParam }
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncFParams::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!FuncFParam::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
        if (!FuncFParam::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<FuncFParams> tmp_p;
    tmp_p.reset(new FuncFParams(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool FuncFParams::addSymTable() {
    for (auto &i: this->sons) {
        auto funcFParam_p = std::dynamic_pointer_cast<FuncFParam>(i);
        if (funcFParam_p) {
            if (!funcFParam_p->addSymTable()) {
                return false;
            }
        }
    }
    return true;
}

bool FuncFParams::getParamTypes(std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> &toReturn) {
    for (auto &i: this->sons) {
        auto funcFParam_p = std::dynamic_pointer_cast<FuncFParam>(i);
        if (funcFParam_p) {
            toReturn.push_back(funcFParam_p->getParamType());
        }
    }
    return true;
}

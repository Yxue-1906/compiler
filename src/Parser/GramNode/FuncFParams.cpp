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

bool FuncFParams::checkValid() {
    bool toReturn = true;
    for (auto ite = sons.begin(); ite < sons.end(); ite += 2) {
        auto funcFParam = std::dynamic_pointer_cast<FuncFParam>(*ite);
        toReturn &= funcFParam->checkValid();
        std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>> tmp;
        if (!funcFParam->getParamType(tmp))
            return false;
        this->params.push_back(tmp);
    }
    return toReturn;
}


bool FuncFParams::getParamTypes(std::vector<std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>>> &toReturn) {
    toReturn = this->params;
    return true;
}

std::shared_ptr<std::vector<std::string>> FuncFParams::getParams() {
    auto toReturn = std::make_shared<std::vector<std::string>>();
    auto ite = sons.begin();
    std::shared_ptr<FuncFParam> funcFParam_p = std::dynamic_pointer_cast<FuncFParam>(*ite);
    for (; ite < sons.end(); ite += 2) {
        funcFParam_p = std::dynamic_pointer_cast<FuncFParam>(*ite);
        if (!funcFParam_p)
            break;
        auto paramNamePair = funcFParam_p->getParam();
        toReturn->push_back(paramNamePair.second);
    }
    return toReturn;
}


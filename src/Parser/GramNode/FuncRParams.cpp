//
// Created by unrelated on 2021/10/20.
//

#include "FuncRParams.h"
#include "Exp.h"
#include "../TokenNode.h"
#include "../../Exception/MyException/MismatchCallTypeException.h"

FuncRParams::FuncRParams(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncRParams");
    setSons(std::move(sons));
}

/**
 * FuncRParams -> Exp { ',' Exp }
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncRParams::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;

    if (!Exp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<FuncRParams> tmp_p;
    tmp_p.reset(new FuncRParams(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool FuncRParams::checkValid() {
    std::shared_ptr<IdentInfo> tmp;
    for (auto &i: sons) {
        auto exp_p = std::dynamic_pointer_cast<Exp>(i);
        if (exp_p) {
            if (exp_p->checkValid()) {
                exp_p->getType(tmp);
                this->params.push_back(tmp);
            } else {
                return false;
            }
        }
    }
    return true;
}

bool FuncRParams::getParamTypes(std::vector<std::shared_ptr<IdentInfo>> &toReturn) {
    if (!this->params.empty()) {
        toReturn = this->params;
        return true;
    }
    return false;
}

std::shared_ptr<std::vector<std::string>> FuncRParams::getParams() {
    auto toReturn = std::make_shared<std::vector<std::string>>();
    auto ite = sons.begin();
    std::shared_ptr<Exp> exp_p;
    for (; ite < sons.end(); ++ite) {
        exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        if (!exp_p)
            break;
        auto tmpVars_p = exp_p->toMidCode();
        toReturn->push_back(*tmpVars_p[0]);
    }
    return toReturn;
}


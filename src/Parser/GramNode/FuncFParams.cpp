//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParams.h"
#include "FuncFParam.h"
#include "../TokenNode.h"

FuncFParams::FuncFParams(std::vector<GramNode *> sons) : GramNode() {
    setGramName("FuncFParams");
    setSons(std::move(sons));
}

/**
 * FuncFParams -> Exp { ',' Exp }
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncFParams::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!FuncFParam::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
        if (!FuncFParam::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new FuncFParams(son_ps));
    return true;
}

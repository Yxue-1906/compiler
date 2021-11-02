//
// Created by unrelated on 2021/10/20.
//

#include "FuncRParams.h"
#include "Exp.h"
#include "../TokenNode.h"

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
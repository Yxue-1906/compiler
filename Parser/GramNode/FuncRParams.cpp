//
// Created by unrelated on 2021/10/20.
//

#include "FuncRParams.h"
#include "Exp.h"
#include "../TokenNode.h"

FuncRParams::FuncRParams(std::vector<GramNode *> sons) : GramNode() {
    setGramName("FuncRParams");
    setSons(std::move(sons));
}

/**
 * FuncRParams -> Exp { ',' Exp }
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncRParams::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;

    if (!Exp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::COMMA);) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new FuncRParams(son_ps));
    return true;
}
//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParams.h"
#include "FuncFParam.h"
#include "../TokenNode.h"

FuncFParams::FuncFParams(std::vector<GramNode *> sons) {
    setGramName("FuncFParams");
    setSons(std::move(sons));
}

bool FuncFParams::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!FuncFParam::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::COMMA);) {
        if (!FuncFParam::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new FuncFParams(son_ps));
    return true;
}

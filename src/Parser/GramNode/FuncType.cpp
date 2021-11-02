//
// Created by unrelated on 2021/10/20.
//

#include "FuncType.h"
#include "../TokenNode.h"

FuncType::FuncType(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncType");
    setSons(std::move(sons));
}

bool FuncType::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::VOIDTK) &&
        !TokenNode::create(son_ps, ite, TokenBase::INTTK)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<FuncType> tmp_p;
    tmp_p.reset(new FuncType(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}


//
// Created by unrelated on 2021/10/20.
//

#include "FuncType.h"
#include "../TokenNode.h"
#include "../../Lexer/Token/VOIDTK.h"

FuncType::FuncType(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncType");
    setSons(std::move(sons));
}

/**
 * FuncType -> 'void' | 'int'
 * @param toAdd
 * @param ite_p
 * @return
 */
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

std::shared_ptr<IdentInfo> FuncType::getFuncType() {
    auto tokenNode = std::dynamic_pointer_cast<TokenNode>(sons.back());
    auto voidTk = std::dynamic_pointer_cast<VOIDTK>(tokenNode->getToken_p());
    if (voidTk) {
        return nullptr;
    }
    return std::make_shared<IdentInfo>(false, 0);
}


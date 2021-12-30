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

bool FuncType::getReturnType(std::shared_ptr<IdentInfo> &toReturn) {
    auto tokenNode = std::dynamic_pointer_cast<TokenNode>(sons.back());
    auto voidTk = std::dynamic_pointer_cast<VOIDTK>(tokenNode->getToken_p());
    if (voidTk) {
        toReturn = nullptr;
        return true;
    }
    toReturn = std::make_shared<IdentInfo>(false, 0);
    return true;
}

bool FuncType::checkValid() {
    return true;
}

bool FuncType::isVoid() {
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[0]);
    if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::VOIDTK)
        return true;
    return false;
}


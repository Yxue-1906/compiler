//
// Created by unrelated on 2021/10/18.
//

#include "Block.h"
#include "../TokenNode.h"
#include "BlockItem.h"
#include "../../Exception/MyException/MismatchReturnForNonVoidException.h"
#include "../../Exception/MyException/MismatchReturnForVoidException.h"

Block::Block(std::vector<std::shared_ptr<GramNode>> sons)
        : GramNode() {
    setGramName("Block");
    setSons(std::move(sons));
}

/**
 * Block -> '{' { BlockItem } '}'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool
Block::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop,
              bool isVoid) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::LBRACE)) {
        return false;
    }
    for (; !TokenBase::isTypeOf(ite, TokenBase::RBRACE) && BlockItem::create(son_ps, ite, isLoop, isVoid););
    if (!TokenNode::create(son_ps, ite, TokenBase::RBRACE)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<Block> tmp_p;
    tmp_p.reset(new Block(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool Block::checkValid() {
    for (auto &i: sons) {
        i->checkValid();
    }
    GramNode::setNowTable(GramNode::getNowTable()->getFormerTable_p());
    return true;
}

/**
 *
 * @param isVoid
 * @return
 */
bool Block::checkReturn(bool isVoid) {
    auto lastItem = std::dynamic_pointer_cast<BlockItem>(*(sons.end() - 2));
    if (!lastItem || !lastItem->hasReturn()) {
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons.back());
        try {
            throw MismatchReturnForNonVoidException(tokenNode_p->getToken_p()->getLineNumber());
        } catch (MyException &e) {
            e.myOutput();
            return false;
        }
    }
    int lineNumber = lastItem->hasReturn();
    try {
        if (isVoid) {
            if (lineNumber > 0)
                throw MismatchReturnForVoidException(lineNumber);
        } else {
            if (lineNumber < 0) {
                auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons.back());
                throw MismatchReturnForNonVoidException(tokenNode_p->getToken_p()->getLineNumber());
            }
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    return true;
}

int Block::getRightBracketLineNumber() {
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons.back());
    return tokenNode_p->getToken_p()->getLineNumber();
}

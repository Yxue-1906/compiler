//
// Created by unrelated on 2021/10/18.
//

#include "Block.h"
#include "../TokenNode.h"
#include "BlockItem.h"

Block::Block(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("Block");
    setSons(std::move(sons));
}

/**
 * Block -> '{' { BlockItem } '}'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Block::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::LBRACE)) {
        return false;
    }
    for (; !TokenBase::isTypeOf(ite, TokenBase::RBRACE) && BlockItem::create(son_ps, ite););
    if (!TokenNode::create(son_ps, ite, TokenBase::RBRACE)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<Block> tmp_p;
    tmp_p.reset(new Block(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}
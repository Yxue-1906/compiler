//
// Created by unrelated on 2021/10/18.
//

#include "Block.h"
#include "../TokenNode.h"
#include "BlockItem.h"

Block::Block(std::vector<GramNode *> sons) {
    setGramName("Block");
    setSons(std::move(sons));
}

bool Block::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::LBRACE)) {
        return false;
    }
    BlockItem::create(son_ps, ite);
}
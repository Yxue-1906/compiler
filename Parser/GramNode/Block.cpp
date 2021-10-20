//
// Created by unrelated on 2021/10/18.
//

#include "Block.h"
#include "../TokenNode.h"
#include "BlockItem.h"

Block::Block(std::vector<GramNode *> sons) : GramNode() {
    setGramName("Block");
    setSons(std::move(sons));
}

/**
 * Block -> '{' { BlockItem } '}'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Block::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::LBRACE)) {
        return false;
    }
    for (; BlockItem::create(son_ps, ite););
    if (!TokenNode::create(son_ps, ite, Token::RBRACE)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new Block(son_ps));
    return true;
}
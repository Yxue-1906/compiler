//
// Created by unrelated on 2021/10/18.
//

#include "Block.h"
#include "../TokenNode.h"

Block::Block(std::vector<GramNode *> sons) {
    setGramName("Block");
    setSons(std::move(sons));
}

bool Block::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!(**ite).isTypeOf(Token::LBRACE)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if (BlockItem::create(nexNode, ite)) {
        son_ps.push_back(nexNode);
    }
}
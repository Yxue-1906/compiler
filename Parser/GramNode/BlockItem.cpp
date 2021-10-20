//
// Created by unrelated on 2021/10/18.
//

#include "BlockItem.h"
#include "Decl.h"
#include "Stmt.h"

BlockItem::BlockItem(std::vector<GramNode *> sons) {
    setGramName("BlockItem");
    setSons(std::move(sons));
}

bool BlockItem::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (Decl::create(nexNode, ite) ||
        Stmt::create(nexNode, ite)) {
        son_ps.push_back(nexNode);
        ite_p = ite;
        toAdd = new BlockItem(son_ps);
        return true;
    } else return false;
}

//
// Created by unrelated on 2021/10/18.
//

#include "BlockItem.h"
#include "Decl.h"
#include "Stmt.h"

BlockItem::BlockItem(std::vector<GramNode *> sons) : GramNode() {
    setGramName("BlockItem");
    setSons(std::move(sons));
}

/**
 * BlockItem -> Decl | Stmt
 * @param toAdd
 * @param ite_p
 * @return
 */
bool BlockItem::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    auto detectDecl = [&ite]() -> bool {
        if (Token::isTypeOf(ite, Token::CONSTTK) ||
            Token::isTypeOf(ite, Token::INTTK))
            return true;
        return false;
    };
    if (detectDecl()) {
        if (!Decl::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new BlockItem(son_ps));
        return true;
    } else {
        if (!Stmt::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new BlockItem(son_ps));
        return true;
    }
}

void BlockItem::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
}

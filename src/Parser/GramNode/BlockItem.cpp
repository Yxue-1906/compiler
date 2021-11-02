//
// Created by unrelated on 2021/10/18.
//

#include "BlockItem.h"
#include "Decl.h"
#include "Stmt.h"

BlockItem::BlockItem(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("BlockItem");
    setSons(std::move(sons));
}

/**
 * BlockItem -> Decl | Stmt
 * @param toAdd
 * @param ite_p
 * @return
 */
bool BlockItem::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    auto detectDecl = [&ite]() -> bool {
        if (TokenBase::isTypeOf(ite, TokenBase::CONSTTK) ||
            TokenBase::isTypeOf(ite, TokenBase::INTTK))
            return true;
        return false;
    };
    if (detectDecl()) {
        if (!Decl::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<BlockItem> tmp_p;
        tmp_p.reset(new BlockItem(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else {
        if (!Stmt::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<BlockItem> tmp_p;
        tmp_p.reset(new BlockItem(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }
}

void BlockItem::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
}

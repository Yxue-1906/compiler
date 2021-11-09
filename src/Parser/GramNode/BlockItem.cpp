//
// Created by unrelated on 2021/10/18.
//

#include "BlockItem.h"
#include "Decl.h"
#include "Stmt.h"
#include "../TokenNode.h"
#include "../../Lexer/Token/RETURNTK.h"
#include "../../Exception/MyException/ConBreakInNonLoopException.h"

BlockItem::BlockItem(std::vector<std::shared_ptr<GramNode>> sons)
        : GramNode() {
    setGramName("BlockItem");
    setSons(std::move(sons));
}

/**
 * BlockItem -> Decl | Stmt
 * @param toAdd
 * @param ite_p
 * @return
 */
bool BlockItem::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p,
                       bool isLoop) {
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
        if (!Stmt::create(son_ps, ite, isLoop)) {
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

bool BlockItem::checkValid() {
    bool toReturn = true;
    for (auto &i: sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

/**
 * get return type of a block
 * @param toReturn return return type by pointer
 * @return true on succeed, false when any error occurred
 */
bool BlockItem::getReturnType(std::shared_ptr<IdentInfo> &toReturn) {
    auto lastStmt = std::dynamic_pointer_cast<Stmt>(sons.back());
    if (!lastStmt) {
        return false;
    }
    return lastStmt->isNonVoidReturn(toReturn);
}


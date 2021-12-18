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
bool
BlockItem::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop,
                  bool isVoid) {
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
        if (!Stmt::create(son_ps, ite, isLoop, isVoid)) {
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
    if (!sons.back()->checkValid())
        return false;
    return true;
}

/**
 * get return type of a block
 * @param toReturn return return type by pointer
 * @return true on succeed, false when any error occurred
 */
bool BlockItem::hasReturn() {
    auto lastStmt_p = std::dynamic_pointer_cast<Stmt>(sons.back());
    if (!lastStmt_p) {
        return false;
    }
    return lastStmt_p->hasReturn();
}

std::string BlockItem::toMidCode() {
    auto gramNode_p = this->sons[0];
    gramNode_p->toMidCode();
    return "";
}


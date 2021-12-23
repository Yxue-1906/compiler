//
// Created by unrelated on 2021/10/18.
//

#include "Decl.h"
#include "ConstDecl.h"
#include "VarDecl.h"

Decl::Decl(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("Decl");
    setSons(std::move(sons));
}

/**
 * Decl -> ConstDecl | VarDecl
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Decl::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenBase::isTypeOf(ite, TokenBase::CONSTTK)) {
        if (!ConstDecl::create(son_ps, ite)) {
            return false;
        }
    } else {
        if (!VarDecl::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<Decl> tmp_p;
    tmp_p.reset(new Decl(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

void Decl::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
}

bool Decl::checkValid() {//todo: realize checkValid of VarDecl
    if (!sons.back()->checkValid())
        return false;
    return true;
}

std::vector<std::shared_ptr<std::string>> Decl::toMidCode() {
    auto gramNode_p = this->sons[0];
    std::vector<std::shared_ptr<std::string>> toReturn;
    gramNode_p->toMidCode();
    return toReturn;
}

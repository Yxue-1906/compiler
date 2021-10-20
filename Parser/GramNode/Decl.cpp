//
// Created by unrelated on 2021/10/18.
//

#include "Decl.h"
#include "ConstDecl.h"
#include "VarDecl.h"

Decl::Decl(std::vector<GramNode *> sons) : GramNode() {
    setGramName("Decl");
    setSons(std::move(sons));
}

/**
 * Decl -> ConstDecl | VarDecl
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Decl::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (Token::isTypeOf(ite, Token::CONSTTK)) {
        if (!ConstDecl::create(son_ps, ite)) {
            return false;
        }
    } else {
        if (!VarDecl::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new Decl(son_ps));
    return true;
}

void Decl::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
}
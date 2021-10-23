//
// Created by unrelated on 2021/10/17.
//

#include "CompUnit.h"
#include "Decl.h"
#include "FuncDef.h"
#include "MainFuncDef.h"

CompUnit::CompUnit(std::vector<GramNode *> sons) : GramNode() {
    setGramName("CompUnit");
    setSons(std::move(sons));
}

/**
 * CompUnit -> {Decl} {FuncDef} MainFuncDef
 * @param toAdd
 * @param ite_p
 * @return
 */
bool CompUnit::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    auto detectDecl = [&ite]() -> bool {
        if (Token::isTypeOf(ite, Token::CONSTTK))return true;
        if (!Token::isTypeOf(ite + 1, Token::IDENFR))return false;
        if (Token::isTypeOf(ite + 2, Token::LPARENT))return false;
        return true;
    };
    auto detectFuncDef = [&ite]() -> bool {
        if (Token::isTypeOf(ite, Token::VOIDTK))return true;
        if (!Token::isTypeOf(ite + 1, Token::IDENFR))return false;
        if (!Token::isTypeOf(ite + 2, Token::LPARENT))return false;
        return true;
    };
    for (; detectDecl() && Decl::create(son_ps, ite););
    for (; detectFuncDef() && FuncDef::create(son_ps, ite););
    if (!MainFuncDef::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new CompUnit(son_ps));
    return true;
}

//
// Created by unrelated on 2021/10/17.
//

#include "CompUnit.h"
#include "Decl.h"
#include "FuncDef.h"
#include "MainFuncDef.h"

CompUnit::CompUnit(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("CompUnit");
    setSons(std::move(sons));
}

/**
 * CompUnit -> {Decl} {FuncDef} MainFuncDef
 * @param toAdd
 * @param ite_p
 * @return
 */
bool CompUnit::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    auto detectDecl = [&ite]() -> bool {
        if (TokenBase::isTypeOf(ite, TokenBase::CONSTTK))return true;
        if (!TokenBase::isTypeOf(ite + 1, TokenBase::IDENFR))return false;
        if (TokenBase::isTypeOf(ite + 2, TokenBase::LPARENT))return false;
        return true;
    };
    auto detectFuncDef = [&ite]() -> bool {
        if (TokenBase::isTypeOf(ite, TokenBase::VOIDTK))return true;
        if (!TokenBase::isTypeOf(ite + 1, TokenBase::IDENFR))return false;
        if (!TokenBase::isTypeOf(ite + 2, TokenBase::LPARENT))return false;
        return true;
    };
    for (; detectDecl() && Decl::create(son_ps, ite););
    for (; detectFuncDef() && FuncDef::create(son_ps, ite););
    if (!MainFuncDef::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<CompUnit> tmp_p;
    tmp_p.reset(new CompUnit(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool CompUnit::checkValid() {
//    std::cout << sons.size() << std::endl;
    bool toReturn = true;
    for (auto &i: this->sons) {
        toReturn &= i->checkValid();
    }
    return toReturn;
}

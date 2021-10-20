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
    Decl::create(son_ps, ite);
    FuncDef::create(son_ps, ite);
    if (!MainFuncDef::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new CompUnit(son_ps));
    return true;
}

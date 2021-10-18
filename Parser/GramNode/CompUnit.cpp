//
// Created by unrelated on 2021/10/17.
//

#include "CompUnit.h"
#include "Decl.h"
#include "FuncDef.h"
#include "MainFuncDef.h"

CompUnit::CompUnit(std::vector<GramNode *> sons) {
    setGramName("CompUnit");
    setSons(std::move(sons));
}

bool CompUnit::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (Decl::create(nexNode, ite)) {
        son_ps.push_back(nexNode);
    }
    if (FuncDef::create(nexNode, ite)) {
        son_ps.push_back(nexNode);
    }
    if (!MainFuncDef::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);
    ite_p = ite;
    toReturn = new CompUnit(son_ps);
    return true;
}

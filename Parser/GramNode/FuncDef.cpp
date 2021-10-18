//
// Created by unrelated on 2021/10/18.
//

#include "FuncDef.h"

FuncDef::FuncDef(std::vector<GramNode *> sons) {
    setGramName("FuncDef");
    setSons(std::move(sons));
}

bool FuncDef::create(GramNode **toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<Token> sons;

}

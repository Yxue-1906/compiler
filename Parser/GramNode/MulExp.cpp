//
// Created by unrelated on 2021/10/18.
//

#include "MulExp.h"

MulExp::MulExp(std::vector<GramNode *> sons) {
    setGramName("MulExp");
    setSons(std::move(sons));
}

bool MulExp::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if(!)
}
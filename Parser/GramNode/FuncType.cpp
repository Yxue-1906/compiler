//
// Created by unrelated on 2021/10/20.
//

#include "FuncType.h"
#include "../TokenNode.h"

FuncType::FuncType(std::vector<GramNode *> sons): GramNode() {
    setGramName("FuncType");
    setSons(std::move(sons));
}

bool FuncType::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::VOIDTK) ||
        !TokenNode::create(son_ps, ite, Token::INTTK)) {
        return false;
    }
    ite_p = ite;
    toAdd.push_back(new FuncType(son_ps));
    return true;
}


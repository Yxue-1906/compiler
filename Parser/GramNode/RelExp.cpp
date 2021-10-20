//
// Created by unrelated on 2021/10/18.
//

#include "RelExp.h"
#include "AddExp.h"
#include "../TokenNode.h"

RelExp::RelExp(std::vector<GramNode *> sons) : GramNode(){
    setGramName("RelExp");
    setSons(std::move(sons));
}

bool RelExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::LEQ) ||
           TokenNode::create(son_ps, ite, Token::GEQ) ||
           TokenNode::create(son_ps, ite, Token::LSS) ||
           TokenNode::create(son_ps, ite, Token::GRE);) {
        if (!AddExp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new RelExp(son_ps));
    return true;
}

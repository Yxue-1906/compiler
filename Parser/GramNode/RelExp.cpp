//
// Created by unrelated on 2021/10/18.
//

#include "RelExp.h"
#include "AddExp.h"
#include "../TokenNode.h"

RelExp::RelExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("RelExp");
    setSons(std::move(sons));
}

/**
 * RelExp -> AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool RelExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    std::swap(toAdd, son_ps);
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    toAdd.push_back(new RelExp(son_ps));
    for (; TokenNode::create(toAdd, ite, Token::LEQ) ||
           TokenNode::create(toAdd, ite, Token::GEQ) ||
           TokenNode::create(toAdd, ite, Token::LSS) ||
           TokenNode::create(toAdd, ite, Token::GRE);) {
        if (!RelExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

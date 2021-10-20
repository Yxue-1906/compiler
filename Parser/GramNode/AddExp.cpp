//
// Created by unrelated on 2021/10/18.
//

#include "AddExp.h"
#include "MulExp.h"
#include "../TokenNode.h"

AddExp::AddExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("AddExp");
    setSons(std::move(sons));
}

/**
 * AddExp -> MulExp | AddExp ('+' | '−') MulExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool AddExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!MulExp::create(son_ps, ite)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, Token::PLUS) || TokenNode::create(son_ps, ite, Token::MINU);) {
        if (!MulExp::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    toAdd.push_back(new AddExp(son_ps));
    return true;
}
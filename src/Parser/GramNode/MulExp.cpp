//
// Created by unrelated on 2021/10/18.
//

#include "MulExp.h"
#include "UnaryExp.h"
#include "../TokenNode.h"

MulExp::MulExp(std::vector<GramNode *> sons) : GramNode() {
    setGramName("MulExp");
    setSons(std::move(sons));
}

/**
 * MulExp -> UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool MulExp::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    std::swap(toAdd, son_ps);
    if (!UnaryExp::create(son_ps, ite)) {
        return false;
    }
    toAdd.push_back(new MulExp(son_ps));
    if (TokenNode::create(toAdd, ite, Token::MULT) ||
        TokenNode::create(toAdd, ite, Token::DIV) ||
        TokenNode::create(toAdd, ite, Token::MOD)) {
        if (!MulExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}
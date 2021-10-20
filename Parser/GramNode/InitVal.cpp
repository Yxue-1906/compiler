//
// Created by unrelated on 2021/10/20.
//

#include "InitVal.h"
#include "../TokenNode.h"
#include "Exp.h"

InitVal::InitVal(std::vector<GramNode *> sons) : GramNode() {
    setGramName("InitVal");
    setSons(std::move(sons));
}

/**
 * InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool InitVal::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (TokenNode::create(son_ps, ite, Token::LBRACE)) {
        if (!InitVal::create(son_ps, ite)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, Token::COMMA);) {
            if (!InitVal::create(son_ps, ite)) {
                return false;
            }
        }
        if (!TokenNode::create(son_ps, ite, Token::RBRACE)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new InitVal(son_ps));
        return true;
    } else if (Exp::create(son_ps, ite)) {
        ite_p = ite;
        toAdd.push_back(new InitVal(son_ps));
        return true;
    }
    return false;
}
//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParam.h"
#include "BType.h"
#include "ConstExp.h"

FuncFParam::FuncFParam(std::vector<GramNode *> sons): GramNode() {
    setGramName("FuncFParam");
    setSons(std::move(sons));
}

bool FuncFParam::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!BType::create(son_ps, ite_p)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite_p, Token::IDENFR)) {
        return false;
    }
    if (TokenNode::create(son_ps, ite_p, Token::LBRACK)) {
        if (!TokenNode::create(son_ps, ite_p, Token::RBRACK)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite_p, Token::LBRACK);) {
            if (!ConstExp::create(son_ps, ite_p)) {
                return false;
            }
            if (!TokenNode::create(son_ps, ite_p, Token::RBRACK)) {
                return false;
            }
        }
    }
    ite_p = ite;
    toAdd.push_back(new FuncFParam(son_ps));
    return true;
}

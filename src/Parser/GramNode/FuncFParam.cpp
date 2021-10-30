//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParam.h"
#include "BType.h"
#include "ConstExp.h"

FuncFParam::FuncFParam(std::vector<GramNode *> sons) : GramNode() {
    setGramName("FuncFParam");
    setSons(std::move(sons));
}

/**
 * FuncFParam -> BType Ident ['[' ']' { '[' ConstExp ']' }]
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncFParam::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!BType::create(son_ps, ite)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    if (TokenNode::create(son_ps, ite, TokenBase::LBRACK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
            if (!ConstExp::create(son_ps, ite)) {
                return false;
            }
            if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
                return false;
            }
        }
    }
    ite_p = ite;
    toAdd.push_back(new FuncFParam(son_ps));
    return true;
}

//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParam.h"
#include "BType.h"
#include "ConstExp.h"

FuncFParam::FuncFParam(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncFParam");
    setSons(std::move(sons));
}

/**
 * FuncFParam -> BType Ident ['[' ']' { '[' ConstExp ']' }]
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncFParam::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
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
    std::shared_ptr<FuncFParam> tmp_p;
    tmp_p.reset(new FuncFParam(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

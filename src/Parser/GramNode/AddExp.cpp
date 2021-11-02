//
// Created by unrelated on 2021/10/18.
//

#include "AddExp.h"
#include "MulExp.h"
#include "../TokenNode.h"

AddExp::AddExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("AddExp");
    setSons(std::move(sons));
}

/**
 * AddExp -> MulExp | AddExp ('+' | '−') MulExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool AddExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    std::swap(toAdd, son_ps);
    if (!MulExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<AddExp> tmp_p;
    tmp_p.reset(new AddExp(son_ps));
    toAdd.push_back(tmp_p);
    if (TokenNode::create(toAdd, ite, TokenBase::PLUS) ||
        TokenNode::create(toAdd, ite, TokenBase::MINU)) {
        if (!AddExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}
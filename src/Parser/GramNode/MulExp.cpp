//
// Created by unrelated on 2021/10/18.
//

#include "MulExp.h"
#include "UnaryExp.h"
#include "../TokenNode.h"

MulExp::MulExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("MulExp");
    setSons(std::move(sons));
}

/**
 * MulExp -> UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool MulExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    std::swap(toAdd, son_ps);
    if (!UnaryExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<MulExp> tmp_p;
    tmp_p.reset(new MulExp(son_ps));
    toAdd.push_back(tmp_p);
    if (TokenNode::create(toAdd, ite, TokenBase::MULT) ||
        TokenNode::create(toAdd, ite, TokenBase::DIV) ||
        TokenNode::create(toAdd, ite, TokenBase::MOD)) {
        if (!MulExp::create(toAdd, ite)) {
            return false;
        }
    }
    ite_p = ite;
    return true;
}

bool MulExp::getType(std::shared_ptr<Info> &toReturn) {
    std::shared_ptr<IdentInfo> tmp;
    for (auto &i: this->sons) {
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(i);
        if (!unaryExp_p)
            continue;
        if (!unaryExp_p.getType(tmp))
            return false;
        if (!tmp)
            return false;
    }
    toReturn = tmp;
    return true;
}

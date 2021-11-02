//
// Created by unrelated on 2021/10/20.
//

#include "LVal.h"
#include "../TokenNode.h"
#include "Exp.h"
#include "../../Lexer/Token/LBRACK.h"

LVal::LVal(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("LVal");
    setSons(std::move(sons));
}

/**
 * LVal → Ident {'[' Exp ']'}
 * @param toAdd
 * @param ite_p
 * @return
 */
bool LVal::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<LVal> tmp_p;
    tmp_p.reset(new LVal(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool LVal::getType(std::shared_ptr<IdentInfo> &toReturn) {
    auto ite = this->sons.begin();
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(*ite);
    ++ite;
    auto tmp = GramNode::getNowTable()->queryIdent(*ident_p->getValue_p());
    toReturn = std::dynamic_pointer_cast<IdentInfo>(tmp);
    if (!toReturn)
        throw DupIdentException(ident_p->getLineNumber());//todo: finish this func
    for (; ite != this->sons.end(); ++ite) {
        if (std::dynamic_pointer_cast<LBRACK>(*ite)) {
            ++ite;
            auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
            std::shared_ptr<IdentInfo> tmp;
            if (exp_p && exp_p->getType(tmp) &&) {
                if (exp_p.)
            }
        }
    }
}

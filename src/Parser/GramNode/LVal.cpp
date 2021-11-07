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

/**
 * get type of lval, be variable or array or array 2d;
 * @param toReturn return value goes here
 * @return true when no error occurred, otherwise false
 */
bool LVal::getType(std::shared_ptr<IdentInfo> &toReturn) {
    auto ite = this->sons.begin();
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(*ite);
    ++ite;
    try {
        auto tmp = GramNode::getNowTable()->queryIdent(*ident_p->getValue_p());
        toReturn = std::dynamic_pointer_cast<IdentInfo>(tmp);
        if (!toReturn) {
            toReturn = nullptr;
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (UndefIdentException &e) {
        e.myOutput();
        toReturn = nullptr;
        return false;
    }
    for (; ite != this->sons.end(); ++ite) {
        if (std::dynamic_pointer_cast<LBRACK>(*ite)) {
            ++ite;
            auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
            std::shared_ptr<IdentInfo> tmp;
            if (exp_p && exp_p->getType(tmp)) {
                // there is an exp and
                // exp can return a type and
                // this type must be a variable
                if (tmp && tmp->getDimension() == 0) {
                    if (toReturn->getDimension() != 0)
                        toReturn = std::make_shared<IdentInfo>(toReturn->checkConst(), toReturn->getDimension() - 1);
                    else {
                        toReturn = nullptr;
                        return false;//todo: check if need throw an exception
                    }
                }
            } else {
                //there should be an exp in the bracket
                //handle fault
            }
        }
    }
    return true;
}

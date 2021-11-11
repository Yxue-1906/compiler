//
// Created by unrelated on 2021/10/18.
//

#include "PrimaryExp.h"
#include "../TokenNode.h"
#include "Exp.h"
#include "Number.h"
#include "LVal.h"
#include "../../Lexer/Token/LPARENT.h"

PrimaryExp::PrimaryExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("PrimaryExp");
    setSons(std::move(sons));
}

/**
 * PrimaryExp → '(' Exp ')' | LVal | Number
 * @param toAdd
 * @param ite_p
 * @return
 */
bool PrimaryExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    auto detectNumber = [&ite]() -> bool {
        if (TokenBase::isTypeOf(ite, TokenBase::INTCON))
            return true;
        return false;
    };
    if (TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
        if (!Exp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<PrimaryExp> tmp_p;
        tmp_p.reset(new PrimaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (detectNumber()) {
        Number::create(son_ps, ite);
        ite_p = ite;
        std::shared_ptr<PrimaryExp> tmp_p;
        tmp_p.reset(new PrimaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else {
        if (!LVal::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<PrimaryExp> tmp_p;
        tmp_p.reset(new PrimaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }
}

bool PrimaryExp::getType(std::shared_ptr<IdentInfo> &toReturn) {
    auto ite = this->sons.begin();
    auto number_p = std::dynamic_pointer_cast<Number>(*ite);
    if (number_p) {
        toReturn = std::make_shared<IdentInfo>(true, 0);
        return true;
    }
    auto lval_p = std::dynamic_pointer_cast<LVal>(*ite);
    if (lval_p) {
        return lval_p->getType(toReturn);
    }
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p && std::dynamic_pointer_cast<LPARENT>(tokenNode_p->getToken_p())) {
        ++ite;
        auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        if (exp_p) {
            return exp_p->getType(toReturn);
        } else {
            //unreachable
        }
    }
    return false;//unreachable
}

bool PrimaryExp::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    if (std::dynamic_pointer_cast<Number>(*ite)) {
        this->type = std::make_shared<IdentInfo>(true, 0);
        return true;
    }
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p) {
        if (std::dynamic_pointer_cast<LPARENT>(tokenNode_p->getToken_p())) {
            ++ite;
            auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
            if (!exp_p->checkValid() || !exp_p->getType(this->type)) {
                //unreachable
                return false;
            }
            return true;
        } else {
            //unreachable
            return false;
        }
    }
    auto lval_p = std::dynamic_pointer_cast<LVal>(*ite);
    if (lval_p) {
        if (!lval_p->checkValid() || !lval_p->getType(this->type))
            return false;
    } else {
        //unreachable
        return false;
    }
    return true;
}

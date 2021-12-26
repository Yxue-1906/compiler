//
// Created by unrelated on 2021/10/18.
//

#include "MulExp.h"
#include "UnaryExp.h"
#include "../TokenNode.h"
#include "../../VM/PCode/MULT.h"
#include "../../VM/PCode/DIV.h"
#include "../../VM/PCode/MOD.h"

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
    if (!UnaryExp::create(son_ps, ite)) {
        return false;
    }
    std::shared_ptr<MulExp> mulExp_p;
    mulExp_p.reset(new MulExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(mulExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::MULT) ||
            TokenNode::create(tmp, ite, TokenBase::DIV) ||
            TokenNode::create(tmp, ite, TokenBase::MOD)) {
            if (!UnaryExp::create(tmp, ite))
                return false;
            mulExp_p.reset(new MulExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(mulExp_p);
    return true;
}

bool
MulExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p,
               __attribute__((unused)) int unUsed) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenNode::create(son_ps, ite, TokenBase::MULT) ||
        TokenNode::create(son_ps, ite, TokenBase::DIV) ||
        TokenNode::create(son_ps, ite, TokenBase::MOD)) {
        if (!UnaryExp::create(son_ps, ite))
            return false;
        auto tokenNode_p = son_ps[0];
        auto unaryExp_p = son_ps[1];
        son_ps.pop_back();
        son_ps.pop_back();
        std::swap(toAdd, son_ps);
        MulExp::create(son_ps, ite, 1);
        son_ps.push_back(tokenNode_p);
        son_ps.push_back(unaryExp_p);
        std::shared_ptr<MulExp> mulExp_p;
        mulExp_p.reset(new MulExp(son_ps));
        ite_p = ite;
        toAdd.push_back(mulExp_p);
        return true;
    } else if (toAdd.size() == 1 && std::dynamic_pointer_cast<UnaryExp>(toAdd.back())) {
        std::swap(toAdd, son_ps);
        std::shared_ptr<MulExp> mulExp_p;
        mulExp_p.reset(new MulExp(son_ps));
        ite_p = ite;
        toAdd.push_back(mulExp_p);
        return true;
    }
    return false;
}

bool MulExp::getType(std::shared_ptr<IdentInfo> &toReturn) {
    if (!this->type)
        return false;
    toReturn = this->type;
    return true;
}

bool MulExp::checkValid() {
    auto ite = sons.begin();
    auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(*ite);
    if (unaryExp_p) {
        if (!unaryExp_p->checkValid() || !unaryExp_p->getType(this->type))
            return false;
        return true;
    }
    auto mulExp_p = std::dynamic_pointer_cast<MulExp>(*ite);
    ite += 2;
    unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(*ite);
    std::shared_ptr<IdentInfo> tmp;
    if (!mulExp_p->checkValid() || !mulExp_p->getType(this->type))
        return false;
    if (!unaryExp_p->checkValid() || !unaryExp_p->getType(tmp))
        return false;
    if (!IdentInfo::mult(this->type, tmp, this->type))
        return false;
    return true;
}

bool MulExp::getLVal(std::shared_ptr<GramNode> &toReturn) {
    if (this->sons.size()) {
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(sons.back());
        return unaryExp_p->getLVal(toReturn);
    }
    return false;
}

int MulExp::toValue() {
    int toReturn = 0;
    if (this->sons.size() > 1) {
        toReturn = std::dynamic_pointer_cast<MulExp>(sons[0])->toValue();
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(sons[2]);
        auto op_p = tokenNode_p->getToken_p();
        if (op_p->getTokenType() == TokenBase::MULT) {
            toReturn *= unaryExp_p->toValue();
        } else if (op_p->getTokenType() == TokenBase::DIV) {
            toReturn /= unaryExp_p->toValue();
        } else {
            toReturn %= unaryExp_p->toValue();
        }
    } else {
        toReturn = std::dynamic_pointer_cast<UnaryExp>(sons[0])->toValue();
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> MulExp::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    if (this->sons.size() > 1) {
        auto mulExp_p = std::dynamic_pointer_cast<MulExp>(sons[0]);
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto op_p = tokenNode_p->getToken_p();
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(sons[2]);
        auto tmpVar1_p = mulExp_p->toMidCode()[0];
        auto tmpVar2_p = unaryExp_p->toMidCode()[0];
        auto tmpVar_p = std::make_shared<std::string>("%" + std::to_string(nowTmpVarCount++));
        if (op_p->getTokenType() == TokenBase::MULT) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::MULT>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else if (op_p->getTokenType() == TokenBase::DIV) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::DIV>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::MOD>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        }
        toReturn.push_back(tmpVar_p);
    } else {
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(sons[0]);
        toReturn = unaryExp_p->toMidCode();
    }
    return toReturn;
}


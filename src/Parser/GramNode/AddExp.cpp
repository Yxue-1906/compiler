//
// Created by unrelated on 2021/10/18.
//

#include <arpa/nameser_compat.h>
#include "AddExp.h"
#include "MulExp.h"
#include "../TokenNode.h"
#include "../../Lexer/Token/PLUS.h"
#include "../../VM/PCode/ADD.h"
#include "../../VM/PCode/MINUS.h"

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
    if (!MulExp::create(son_ps, ite))
        return false;
    std::shared_ptr<AddExp> addExp_p;
    addExp_p.reset(new AddExp(son_ps));
    for (;;) {
        std::vector<std::shared_ptr<GramNode>> tmp;
        tmp.push_back(addExp_p);
        if (TokenNode::create(tmp, ite, TokenBase::PLUS) ||
            TokenNode::create(tmp, ite, TokenBase::MINU)) {
            if (!MulExp::create(tmp, ite))
                return false;
            addExp_p.reset(new AddExp(tmp));
        } else {
            break;
        }
    }
    ite_p = ite;
    toAdd.push_back(addExp_p);
    return true;
}

bool
AddExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p,
               __attribute__((unused)) int unUsed) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenNode::create(son_ps, ite, TokenBase::PLUS) ||
        TokenNode::create(son_ps, ite, TokenBase::MINU)) {
        if (!MulExp::create(son_ps, ite))
            return false;
        auto tokenNode_p = son_ps[0];
        auto mulExp_p = son_ps[1];
        son_ps.pop_back();
        son_ps.pop_back();
        std::swap(toAdd, son_ps);
        AddExp::create(son_ps, ite, 1);
        son_ps.push_back(tokenNode_p);
        son_ps.push_back(mulExp_p);
        std::shared_ptr<AddExp> addExp_p;
        addExp_p.reset(new AddExp(son_ps));
        ite_p = ite;
        toAdd.push_back(addExp_p);
        return true;
    } else if (toAdd.size() == 1 && std::dynamic_pointer_cast<MulExp>(toAdd.back())) {
        std::swap(toAdd, son_ps);
        std::shared_ptr<AddExp> addExp_p;
        addExp_p.reset(new AddExp(son_ps));
        ite_p = ite;
        toAdd.push_back(addExp_p);
        return true;
    }
    return false;
}

bool AddExp::getType(std::shared_ptr<IdentInfo> &toReturn) {
    if (!this->type)
        return false;
    toReturn = this->type;
    return true;
}

bool AddExp::checkValid() {
    auto ite = sons.begin();
    auto mulExp_p = std::dynamic_pointer_cast<MulExp>(*ite);
    if (mulExp_p) {
        if (!mulExp_p->checkValid() || !mulExp_p->getType(this->type))
            return false;
        return true;
    }
    auto addExp_p = std::dynamic_pointer_cast<AddExp>(*ite);
    ite += 2;
    mulExp_p = std::dynamic_pointer_cast<MulExp>(*ite);
    std::shared_ptr<IdentInfo> tmp;
    if (!addExp_p->checkValid() || !addExp_p->getType(this->type))
        return false;
    if (!mulExp_p->checkValid() || !mulExp_p->getType(tmp))
        return false;
    if (!IdentInfo::add(this->type, tmp, this->type))
        return false;

    return true;
}

bool AddExp::getLVal(std::shared_ptr<GramNode> &toReturn) {
    if (this->sons.size() == 1) {
        auto mulExp_p = std::dynamic_pointer_cast<MulExp>(sons.back());
        return mulExp_p->getLVal(toReturn);
    }
    return false;
}

int AddExp::toValue() {
    int toReturn = 0;
    if (this->sons.size() > 1) {
        toReturn = std::dynamic_pointer_cast<AddExp>(sons[0])->toValue();
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto mulExp_p = std::dynamic_pointer_cast<MulExp>(sons[2]);
        if (std::dynamic_pointer_cast<PLUS>(tokenNode_p->getToken_p())) {
            toReturn += mulExp_p->toValue();
        } else {
            toReturn -= mulExp_p->toValue();
        }
    } else {
        toReturn = std::dynamic_pointer_cast<MulExp>(sons[0])->toValue();
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> AddExp::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    if (this->sons.size() > 1) {
        auto addExp_p = std::dynamic_pointer_cast<AddExp>(sons[0]);
        auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
        auto op_p = tokenNode_p->getToken_p();
        auto mulExp_p = std::dynamic_pointer_cast<MulExp>(sons[2]);
        auto tmpVar1_p = addExp_p->toMidCode()[0];
        auto tmpVar2_p = mulExp_p->toMidCode()[0];
        auto tmpVar_p = symTableGenCode.getNewTmpVarName();
        if (op_p->getTokenType() == TokenBase::PLUS) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::ADD>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        } else {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::MINUS>(*tmpVar1_p, *tmpVar2_p, *tmpVar_p));
        }
        toReturn.push_back(tmpVar_p);
    } else {
        auto mulExp_p = std::dynamic_pointer_cast<MulExp>(sons[0]);
        toReturn = mulExp_p->toMidCode();
    }
    return toReturn;
}

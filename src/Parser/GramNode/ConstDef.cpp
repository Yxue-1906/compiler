//
// Created by unrelated on 2021/10/18.
//

#include "ConstDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "ConstInitVal.h"
#include "../../Lexer/Token/LBRACK.h"
#include "../ErrorNode.h"
#include "../../VM/PCode/ALLO.h"
#include "../../VM/PCode/STO.h"

ConstDef::ConstDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("ConstDef");
    setSons(std::move(sons));
}

/**
 * ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_BRACKET);
        }
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::ASSIGN)) {
        return false;
    }
    if (!ConstInitVal::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<ConstDef> tmp_p;
    tmp_p.reset(new ConstDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool ConstDef::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    ++ite;
    int dimension = 0;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lb = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lb)
                dimension++;
        } else {
            toReturn &= (*ite)->checkValid();
        }
    }
    try {
        if (!GramNode::getNowTable()->addIdent(*ident_p->getValue_p(), std::make_shared<IdentInfo>(true, dimension))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    return true;
}

std::vector<std::shared_ptr<std::string>> ConstDef::toMidCode() {
    auto ite = this->sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    std::vector<std::shared_ptr<std::string>> toReturn;
    ite += 2;
    std::shared_ptr<std::string> ident =
            std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
    auto dimension_p = std::make_shared<std::vector<int>>();
    for (auto constExp_p = std::dynamic_pointer_cast<ConstExp>(*ite); ite < this->sons.end(); ite += 3) {
        constExp_p = std::dynamic_pointer_cast<ConstExp>(*ite);
        if (!constExp_p)
            break;
        int toPush = constExp_p->toValue();
        dimension_p->push_back(toPush);
    }
    int size = 1;
    for (int i: *dimension_p) {
        size *= i;
    }
    auto constInitVal_p = std::dynamic_pointer_cast<ConstInitVal>(*ite);
    auto values_p = constInitVal_p->toValues();
    symTableGenCode.addConst(*ident, dimension_p, values_p);
    auto varType = symTableGenCode.searchVar(*ident);
    MidCodeSequence.push_back(std::make_shared<INTERPRETER::ALLO>(varType->tmpName, size));
    for (int i = 0; i < values_p->size(); ++i) {
        auto value_p = std::make_shared<std::string>(std::to_string((*values_p)[i]));
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::STO>(*value_p, varType->tmpName, std::to_string(i)));
    }
    return toReturn;
}


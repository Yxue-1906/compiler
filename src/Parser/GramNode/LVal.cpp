//
// Created by unrelated on 2021/10/20.
//

#include "LVal.h"
#include "../TokenNode.h"
#include "Exp.h"
#include "../../Lexer/Token/LBRACK.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"
#include "../../Lexer/Token/RBRACK.h"
#include "../../VM/PCode/ALLO.h"
#include "../../VM/PCode/MULT.h"
#include "../../VM/PCode/ADD.h"
#include "../../VM/PCode/LOD.h"
#include "../../VM/PCode/LODA.h"

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
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_BRACKET);
        }
    }
    ite_p = ite;
    std::shared_ptr<LVal> tmp_p;
    tmp_p.reset(new LVal(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool LVal::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    auto type_tmp = GramNode::getNowTable()->queryVar(*ident_p->getValue_p());
    try {
        if (!type_tmp)
            throw UndefIdentException(ident_p->getLineNumber());
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    int dimension = type_tmp->getDimension();
    ite++;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lb = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lb)
                dimension--;
        } else {
            toReturn &= (*ite)->checkValid();
        }
    }
    this->type = std::make_shared<IdentInfo>(type_tmp->checkConst(), dimension);
    return toReturn;
}

/**
 * get type of lval, be variable or array or array 2d;
 * @param toReturn return value goes here
 * @return true when no error occurred, otherwise false
 */
bool LVal::getType(std::shared_ptr<IdentInfo> &toReturn) {
    if (this->type) {
        toReturn = this->type;
        return true;
    }
    return false;
}

int LVal::toValue() {
    auto ite = this->sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    auto varName = *ident_p->getValue_p();
    auto varType = LVal::symTableGenCode.searchVar(varName);
    //varType should not be empty
    ite += 2;
    int offset = 0;
    auto varDimension = *varType->dimension_p;
    auto varValues = *varType->values_p;
    for (int i = 1; ite < this->sons.end(); ite += 3, i++) {
        auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        int pre_offset = 1;
        for (int j = i; j < varDimension.size(); ++j) {
            pre_offset *= varDimension[j];
        }
        offset += pre_offset * exp_p->toValue();
    }
    return varValues[offset];
}

std::vector<std::shared_ptr<std::string>> LVal::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    auto ite = this->sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
    auto varName = *ident_p;
    auto varType = symTableGenCode.searchVar(varName);
    varName = varType->tmpName;
    ite += 2;

    auto offset_p = symTableGenCode.getNewTmpVarName();
    MidCodeSequence.push_back(std::make_shared<INTERPRETER::ALLO>(*offset_p, 1));
    auto varDimension = *varType->dimension_p;
    int i = 1;
    for (; ite < this->sons.end(); ite += 3, i++) {
        auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        auto expTmpVars = exp_p->toMidCode();
        std::string dimension = *expTmpVars[0];
        int pre_offset = 1;
        for (int j = i; j < varDimension.size(); ++j) {
            pre_offset *= varDimension[j];
        }
        auto tmpOffset_p = symTableGenCode.getNewTmpVarName();
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::MULT>(dimension,
                                                                      std::to_string(pre_offset),
                                                                      *tmpOffset_p));
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::ADD>(*offset_p, *tmpOffset_p, *offset_p));
    }
    if (i <= varDimension.size()) {
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::LODA>(*offset_p, varName, *offset_p));
    } else {
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::LOD>(*offset_p, varName, *offset_p));
    }
    toReturn.push_back(offset_p);
    return toReturn;
}

std::pair<std::shared_ptr<std::string>, std::shared_ptr<std::string>> LVal::getAddr() {
    std::pair<std::shared_ptr<std::string>, std::shared_ptr<std::string>> toReturn;
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
    auto varName = *ident_p;
    auto varType = symTableGenCode.searchVar(varName);
    varName = varType->tmpName;
    ite += 2;

    auto offset_p = symTableGenCode.getNewTmpVarName();
    MidCodeSequence.push_back(std::make_shared<INTERPRETER::ALLO>(*offset_p, 1));
    auto varDimension = *varType->dimension_p;
    for (int i = 1; ite < sons.end(); ite += 3, i++) {
        auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        auto expTmpVars = exp_p->toMidCode();
        std::string dimension = *expTmpVars[0];
        int pre_offset = 1;
        for (int j = i; j < varDimension.size(); ++j) {
            pre_offset *= varDimension[j];
        }
        auto tmpOffset_p = symTableGenCode.getNewTmpVarName();
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::MULT>(dimension,
                                                                      std::to_string(pre_offset),
                                                                      *tmpOffset_p));
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::ADD>(*offset_p, *tmpOffset_p, *offset_p));
    }
    toReturn.first = std::make_shared<std::string>(varName);
    toReturn.second = offset_p;
    return toReturn;
}



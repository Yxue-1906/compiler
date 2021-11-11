//
// Created by unrelated on 2021/10/18.
//

#include "FuncDef.h"
#include "FuncType.h"
#include "../TokenNode.h"
#include "FuncFParams.h"
#include "Block.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightParenthesisException.h"
#include "../../Exception/MyException/MismatchReturnForVoidException.h"
#include "../../Exception/MyException/MismatchReturnForNonVoidException.h"
#include "../../Lexer/Token/RBRACK.h"

FuncDef::FuncDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncDef");
    setSons(std::move(sons));
}

/**
 * FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!FuncType::create(son_ps, ite)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
        return false;
    }
    if (!TokenBase::isTypeOf(ite, TokenBase::RPARENT)) {
//        if (!FuncFParams::create(son_ps, ite))
//            return false;
        FuncFParams::create(son_ps, ite);
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
        ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
    }
    if (!Block::create(son_ps, ite, false)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<FuncDef> tmp_p;
    tmp_p.reset(new FuncDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

/**
 *
 * @return
 */
bool FuncDef::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    auto funcType_p = std::dynamic_pointer_cast<FuncType>(*ite);
    std::shared_ptr<IdentInfo> returnType;
    if (!funcType_p->getReturnType(returnType)) {
        //unreachable
        return false;
    }
    ++ite;
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    ite += 2;
    auto funcFParams = std::dynamic_pointer_cast<FuncFParams>(*ite);
    std::vector<std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>>> params;
    if (funcFParams) {
        if (!funcFParams->checkValid() || !funcFParams->getParamTypes(params)) {
            //unreachable
            return false;
        }
    }
    try {
        for (auto &i: params) {
            if (GramNode::getNowTable()->addIdent(*i.first->getValue_p(), i.second)) {
                throw DupIdentException(i.first->getLineNumber());
            }
        }
        std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> tmp_params;
        tmp_params.reserve(params.size());
        for (auto &i: params) {
            tmp_params.emplace_back(*i.first->getValue_p(), i.second);
        }
        if (!GramNode::getNowTable()->addIdent(*ident_p->getValue_p(),
                                               std::make_shared<FuncInfo>(returnType, tmp_params))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    GramNode::setNowTable(std::make_shared<SymTable>(GramNode::getNowTable()));
    auto block_p = std::dynamic_pointer_cast<Block>(sons.back());
    if (!block_p->checkValid())
        return false;
    toReturn &= block_p->checkReturn(returnType == nullptr);
    return toReturn;
}

/*
bool FuncDef::addIdent() {
    //init itra
    auto ite = sons.begin();
    auto funcType = std::dynamic_pointer_cast<FuncType>(*ite);
    ite++;
    if (!funcType) {
        //unreachable
        //handle fault
    }

    //get return type
    std::shared_ptr<IdentInfo> returnType;
    funcType->getReturnType(returnType);
    auto tokenNode = std::dynamic_pointer_cast<TokenNode>(*ite);
    ite++;

    //get func name
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode->getToken_p());
    std::string name = *ident_p->getValue_p();
    ite += 2;

    //set new Table
    GramNode::setNowTable(std::make_shared<SymTable>(GramNode::getNowTable()));
    bool toReturn = true;

    //check param valid
    auto funcFParams = std::dynamic_pointer_cast<FuncFParams>(*ite);
    toReturn &= funcFParams->checkValid();

    //get params type
//    std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> params;
//    funcFParams->getParamTypes(params);

    //add params
//    for (auto &i: params) {
//        auto paramName = i.first;
//        auto paramType = i.second;
//        try {
//            if (!GramNode::nowTable_p->addIdent(paramName, paramType)) {
//                toReturn = false;
//                throw DupIdentException(ident_p->getLineNumber());
//            }
//        } catch (DupIdentException &e) {
//            e.myOutput();
//        }
//    }

    //check block valid
    auto block_p = std::dynamic_pointer_cast<Block>(sons.back());
    if (!block_p) {
        //unreachable
        std::cout << __FILE__ << ':' << __LINE__ << ':' << "Unreachable" << std::endl;
    }
    block_p->checkValid();

    //check return type
    std::shared_ptr<IdentInfo> returnTypeFromBlock;
    try {
        if (returnType) {//todo: refactor
            if (block_p->getReturnType(returnTypeFromBlock) &&
                returnTypeFromBlock->getDimension() != returnType->getDimension())
                throw MismatchReturnForVoidException(ident_p->getLineNumber());
        } else {
            if (!block_p->checkReturn(returnTypeFromBlock) ||
                returnTypeFromBlock->getDimension() != returnType->getDimension())
                throw MismatchReturnForNonVoidException(block_p->getRightBracketLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    return toReturn;
}*/

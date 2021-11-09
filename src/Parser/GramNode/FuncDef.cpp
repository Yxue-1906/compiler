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
        if (!FuncFParams::create(son_ps, ite))
            return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
        ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
    }
    if (!Block::create(son_ps, ite, false, false)) {
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
    for (auto &i: sons) {
        i->updateLineNumber();
        auto errorNode = std::dynamic_pointer_cast<ErrorNode>(i);
        try {
            if (errorNode) {
                switch (errorNode->errorType) {
                    case ErrorNode::ErrorType::RIGHT_PARENTHESIS:
                        throw MissingRightParenthesisException(GramNode::nowLine);
                    default:
                        //unreachable
                        std::cout << __FILE__ << ':' << __LINE__ << ':' << "Unreachable" << std::endl;
                        break;
                }
            }
        } catch (MissingRightParenthesisException &e) {
            e.myOutput();
            return false;
        }
    }
    return true;
}

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
    GramNode::nowTable_p = std::make_shared<SymTable>(GramNode::nowTable_p);
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
        if (returnType) {
            if (block_p->getReturnType(returnTypeFromBlock) &&
                returnTypeFromBlock->getDimension() != returnType->getDimension())
                throw MismatchReturnForVoidException(ident_p->getLineNumber());
        } else {
            if (!block_p->getReturnType(returnTypeFromBlock) ||
                returnTypeFromBlock->getDimension() != returnType->getDimension())
                throw MismatchReturnForNonVoidException(ident_p->getLineNumber());
        }
    } catch (MismatchReturnForVoidException &e) {
        e.myOutput();
        return false;
    } catch (MismatchReturnForNonVoidException &e) {
        e.myOutput();
        return false;
    }
    return toReturn;
}
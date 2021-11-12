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
    std::vector<std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>>> params_tmp;
    if (funcFParams) {
        if (!funcFParams->checkValid() || !funcFParams->getParamTypes(params_tmp)) {
            return false;
        }
    }
    std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> params;
    for (auto &i: params_tmp) {
        params.push_back(std::make_pair(*i.first->getValue_p(), i.second));
    }
    try {
        if (!GramNode::getNowTable()->addIdent(*ident_p->getValue_p(),
                                               std::make_shared<FuncInfo>(returnType, params))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    GramNode::setNowTable(std::make_shared<SymTable>(GramNode::getNowTable()));
    for (auto &i: params_tmp) {
        try {
            if (!GramNode::getNowTable()->addIdent(*i.first->getValue_p(), i.second))
                throw DupIdentException(i.first->getLineNumber());
        } catch (MyException &e) {
            e.myOutput();
        }
    }
    auto block_p = std::dynamic_pointer_cast<Block>(sons.back());
    if (!block_p->checkValid())
        return false;
    toReturn &= block_p->checkReturn(returnType == nullptr);
    return toReturn;
}

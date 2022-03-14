//
// Created by unrelated on 2021/10/18.
//

#include "UnaryExp.h"
#include "../TokenNode.h"
#include "FuncRParams.h"
#include "PrimaryExp.h"
#include "UnaryOp.h"
#include "../../Exception/MyException/MismatchParamNumException.h"
#include "../../Exception/MyException/MismatchCallTypeException.h"
#include "../ErrorNode.h"
#include "../../VM/PCode/MINUS.h"
#include "../../VM/PCode/NOT.h"
#include "../../VM/PCode/CALL.h"
#include "../../VM/PCode/LOD.h"
#include "../../VM/PCode/ALLO.h"

UnaryExp::UnaryExp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("UnaryExp");
    setSons(std::move(sons));
}

/**
 * UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')'| UnaryOp UnaryExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool UnaryExp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenBase::isTypeOf(ite, TokenBase::PLUS) ||
        TokenBase::isTypeOf(ite, TokenBase::MINU) ||
        TokenBase::isTypeOf(ite, TokenBase::NOT)) {
        if (!UnaryOp::create(son_ps, ite)) {
            return false;
        }
        if (!UnaryExp::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<UnaryExp> tmp_p;
        tmp_p.reset(new UnaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::IDENFR) &&
               TokenBase::isTypeOf(ite + 1, TokenBase::LPARENT)) {
        TokenNode::create(son_ps, ite, TokenBase::IDENFR);
        TokenNode::create(son_ps, ite, TokenBase::LPARENT);
//        if (!TokenBase::isTypeOf(ite, TokenBase::RPARENT)) {
//            if (!FuncRParams::create(son_ps, ite))
//                return false;
//        }
        FuncRParams::create(son_ps, ite);
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
        }
        ite_p = ite;
        std::shared_ptr<UnaryExp> tmp_p;
        tmp_p.reset(new UnaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (PrimaryExp::create(son_ps, ite)) {
        ite_p = ite;
        std::shared_ptr<UnaryExp> tmp_p;
        tmp_p.reset(new UnaryExp(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }
    return false;
}

bool UnaryExp::getType(std::shared_ptr<IdentInfo> &toReturn) {
    if (this->type) {
        toReturn = this->type;
        return true;
    }
    return false;
}

bool UnaryExp::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    auto primaryExp_p = std::dynamic_pointer_cast<PrimaryExp>(*ite);
    if (primaryExp_p) {
        if (primaryExp_p->checkValid()) {
            primaryExp_p->getType(this->type);
            return true;
        }
        return false;
    }
    auto unaryOp_p = std::dynamic_pointer_cast<UnaryOp>(*ite);
    if (unaryOp_p) {
        ite++;
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(*ite);
        if (unaryExp_p->checkValid()) {
            unaryExp_p->getType(this->type);
            return true;
        }
        return false;
    }

    //
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    std::shared_ptr<FuncInfo> funcInfo;
    try {
        funcInfo = GramNode::getNowTable()->queryFunc(*ident_p->getValue_p());
        if (!funcInfo)
            throw UndefIdentException(ident_p->getLineNumber());
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    ite += 2;
    auto funcRParams = std::dynamic_pointer_cast<FuncRParams>(*ite);
    std::vector<std::shared_ptr<IdentInfo>> params;
    if (funcRParams) {
        try {
            if (!funcRParams->checkValid() || !funcRParams->getParamTypes(params))
                throw MismatchCallTypeException(ident_p->getLineNumber());
        } catch (MyException &e) {
            e.myOutput();
            return false;
        }
        ++ite;
    }
    (*ite)->checkValid();
    try {
        if (!funcInfo->checkParamTypes(params)) {
            switch (FuncInfo::getLastError()) {
                case FuncInfo::ErrorType::MISMATCH_PARAM_NUM:
                    throw MismatchParamNumException(ident_p->getLineNumber());
                case FuncInfo::ErrorType::MISMATCH_CALL_TYPE:
                    throw MismatchCallTypeException(ident_p->getLineNumber());
                default:
                    //unreachable
                    return false;
            }
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    this->type = funcInfo->getReturnType();
    return true;
}

bool UnaryExp::getLVal(std::shared_ptr<GramNode> &toReturn) {
    if (this->sons.size() == 1) {
        auto primaryExp_p = std::dynamic_pointer_cast<PrimaryExp>(sons.back());
        if (!primaryExp_p)
            return false;
        return primaryExp_p->getLVal(toReturn);
    }
    return false;
}

int UnaryExp::toValue() {
    auto primaryExp_p = std::dynamic_pointer_cast<PrimaryExp>(this->sons[0]);
    if (primaryExp_p) {
        return primaryExp_p->toValue();
    } else {
        auto unaryOp_p = std::dynamic_pointer_cast<UnaryOp>(this->sons[0]);
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(this->sons[1]);
        int toReturn = unaryExp_p->toValue();
        if (unaryOp_p->getType() == UnaryOp::Type::PLUS) {
            return toReturn;
        } else {
            return -toReturn;
        }
    }
}

std::vector<std::shared_ptr<std::string>> UnaryExp::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    auto primaryExp_p = std::dynamic_pointer_cast<PrimaryExp>(this->sons[0]);
    if (primaryExp_p) {
        toReturn = primaryExp_p->toMidCode();
    } else {
        auto unaryOp_p = std::dynamic_pointer_cast<UnaryOp>(sons[0]);
        if (unaryOp_p) {
            auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(sons[1]);
            if (unaryOp_p->getType() == UnaryOp::Type::MINUS) {
                auto tmpVar1_p = unaryExp_p->toMidCode()[0];
                auto tmpVar_p = symTableGenCode.getNewTmpVarName();
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::MINUS>("0", *tmpVar1_p, *tmpVar_p));
                toReturn.push_back(tmpVar_p);
            } else if (unaryOp_p->getType() == UnaryOp::Type::NOT) {
                auto tmpVar1_p = unaryExp_p->toMidCode()[0];
                auto tmpVar_p = symTableGenCode.getNewTmpVarName();
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::NOT>(*tmpVar1_p, *tmpVar_p));
                toReturn.push_back(tmpVar_p);
            } else {
                toReturn = unaryExp_p->toMidCode();
            }
        } else {
            //todo:generate midcode for function call
            auto ite = sons.begin();
            auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
            auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
            ite += 2;
            std::vector<std::string> params;
            auto funcRParams_p = std::dynamic_pointer_cast<FuncRParams>(*ite);
            if (funcRParams_p) {
                params = *funcRParams_p->getParams();
            }
            auto funcInfo = symTableGenCode.searchFunc_s(*ident_p);
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::CALL>(*ident_p, params, *funcInfo));
            auto tmpVar_p = symTableGenCode.getNewTmpVarName();
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::ALLO>(*tmpVar_p, 1));
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::LOD>(*tmpVar_p, "%ret", "0"));
            toReturn.push_back(tmpVar_p);
            return toReturn;
        }
    }
    return toReturn;
}

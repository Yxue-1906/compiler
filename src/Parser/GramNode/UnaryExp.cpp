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
#include "../../Lexer/Token/LPARENT.h"
#include "../ErrorNode.h"

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
        if (!TokenBase::isTypeOf(ite, TokenBase::RPARENT)) {
            if (!FuncRParams::create(son_ps, ite))
                return false;
        }
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
        funcInfo = std::dynamic_pointer_cast<FuncInfo>(GramNode::getNowTable()->queryIdent(*ident_p->getValue_p()));
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
        if (!funcRParams->checkValid() || !funcRParams->getParamTypes(params))
            return false;
    }
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

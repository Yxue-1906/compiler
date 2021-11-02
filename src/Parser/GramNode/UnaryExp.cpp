//
// Created by unrelated on 2021/10/18.
//

#include "UnaryExp.h"
#include "../TokenNode.h"
#include "FuncRParams.h"
#include "PrimaryExp.h"
#include "UnaryOp.h"
#include "../../Exception/MyException/MismatchParmNumException.h"

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
        if (!TokenBase::isTypeOf(ite, TokenBase::RPARENT))
            if (!FuncRParams::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
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

bool UnaryExp::getType(std::shared_ptr<Info> &toReturn) {
    std::shared_ptr<IdentInfo> tmp;
    auto ite = this->sons.begin();
    for (; ite != this->sons.end(); ++ite) {
        auto primaryExp_p = std::dynamic_pointer_cast<PrimaryExp>(*ite);
        if (primaryExp_p) {
            if (!primaryExp_p->getType(tmp))
                return false;
            if (!tmp)
                return false;
            continue;
        }
        auto ident_p = std::dynamic_pointer_cast<IDENFR>(*ite);
        if (ident_p) {
            try {
                auto info = GramNode::nowTable_p->queryIdent(*ident_p->getValue_p());
                if (!info) {
                    // variable with the name does not exist
                    throw UndefIdentException(ident_p->getLineNumber());
                }
                std::shared_ptr<FuncInfo> funcInfo = std::dynamic_pointer_cast<FuncInfo>(info);
                if (!funcInfo)
                    throw UndefIdentException(ident_p->getLineNumber());
                if (!tmp || funcInfo->checkReturnType(tmp))
                    tmp = funcInfo->getReturnType();
                else
                    return false;
                ite += 2;
                auto funcRParams_p = std::dynamic_pointer_cast<FuncRParams>(*ite);
                std::vector<std::shared_ptr<IdentInfo>> toCheck;
                if (funcRParams_p) {
                    toCheck = funcRParams_p->getParamTypes();
                }
                if (!funcInfo->checkParamTypes(toCheck)) {
                    int errorno = FuncInfo::getLastError();
                    switch (errorno) {
                        case 1:
                            throw MismatchParmNumException(ident_p->getLineNumber());
                        case 2:
                            throw Mism//todo: throw right exception
                    }
                }
            } catch (UndefIdentException &e) {
                e.myOutput();
                return false;
            } catch ()
        }
    }
}

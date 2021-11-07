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

bool UnaryExp::getType(std::shared_ptr<IdentInfo> &toReturn) {
    std::shared_ptr<IdentInfo> tmp;
    auto ite = this->sons.begin();
    auto primaryExp_p = std::dynamic_pointer_cast<PrimaryExp>(*ite);
    if (primaryExp_p) {
        return primaryExp_p->getType(toReturn);
    }
    auto unaryOp_p = std::dynamic_pointer_cast<UnaryOp>(*ite);
    if (unaryOp_p) {
        ++ite;
        auto unaryExp_p = std::dynamic_pointer_cast<UnaryExp>(*ite);
        return unaryExp_p->getType(toReturn);
    }
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p) {
        auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
        auto info = GramNode::getNowTable()->queryIdent(*ident_p->getValue_p());
        toReturn = std::dynamic_pointer_cast<IdentInfo>(info);
        try {
            if (!toReturn) {
                throw UndefIdentException(ident_p->getLineNumber());
            }
        } catch (UndefIdentException &e) {
            e.myOutput();
            return false;
        }
        ++ite;
        try {
            for (; ite != this->sons.end(); ++ite) {
                tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
                if (std::dynamic_pointer_cast<LPARENT>(tokenNode_p->getToken_p())) {
                    ++ite;
                    if (ite == this->sons.end()) {
                        //will it?
                        toReturn = nullptr;
                        std::cout << __FILE__ << ':' << __LINE__ << ':' << "reach son end here" << std::endl;
                        return false;
                    }
                    auto funcRParams_p = std::dynamic_pointer_cast<FuncRParams>(*ite);
                    std::vector<std::shared_ptr<IdentInfo>> params;
                    try {
                        if (funcRParams_p) {
                            params = funcRParams_p->getParamTypes(ident_p->getLineNumber());
                        }
                    }

                }
            }
        } catch () {

        }
    }
}

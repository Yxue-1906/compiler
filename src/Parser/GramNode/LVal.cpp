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
            return false;
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
    std::shared_ptr<IdentInfo> type;
    try {
        type = std::dynamic_pointer_cast<IdentInfo>(
                GramNode::getNowTable()->queryIdent(*ident_p->getValue_p())
        );
        if (!type) {
            throw UndefIdentException(ident_p->getLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    ite++;
    int dimension = type->getDimension();
    while (true) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (!tokenNode_p)
            break;
        auto lb = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
        ++ite;
        auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        toReturn &= exp_p->checkValid();
        if (!toReturn)
            break;
        ++ite;
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        try {
            if (!tokenNode_p) {
                auto errorNode_p = std::dynamic_pointer_cast<ErrorNode>(*ite);
                switch (errorNode_p->getErrorType()) {
                    case ErrorNode::ErrorType::RIGHT_BRACKET:
                        throw MissingRightBracketException(errorNode_p->getLineNumber());
                    default:
                        //unreachable
                        return false;
                }
            }
        } catch (MyException &e) {
            e.myOutput();
            return false;
        }
        auto rb = std::dynamic_pointer_cast<RBRACK>(*ite);
        dimension--;
        ++ite;
    }
    this->type = std::make_shared<IdentInfo>(type->checkConst(), dimension);
    return toReturn;
}

/**
 * get type of lval, be variable or array or array 2d;
 * @param toReturn return value goes here
 * @return true when no error occurred, otherwise false
 */
bool LVal::getType(std::shared_ptr<IdentInfo> &toReturn) {
    toReturn = this->type;
    if (!this->type)
        return false;
    return true;
}



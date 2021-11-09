//
// Created by unrelated on 2021/10/20.
//

#include "FuncFParam.h"
#include "BType.h"
#include "ConstExp.h"
#include "../../Lexer/Token/LBRACK.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"

FuncFParam::FuncFParam(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("FuncFParam");
    setSons(std::move(sons));
}

/**
 * FuncFParam -> BType Ident ['[' ']' { '[' ConstExp ']' }]
 * @param toAdd
 * @param ite_p
 * @return
 */
bool FuncFParam::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!BType::create(son_ps, ite)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    if (TokenNode::create(son_ps, ite, TokenBase::LBRACK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
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
    }
    ite_p = ite;
    std::shared_ptr<FuncFParam> tmp_p;
    tmp_p.reset(new FuncFParam(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool FuncFParam::checkValid() {
    int dimension = 0;
    auto ite = sons.begin() + 1;
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    for (; ite != sons.end(); ++ite) {
        (*ite)->updateLineNumber();
        auto errorNode = std::dynamic_pointer_cast<ErrorNode>(*ite);
        try {
            if (errorNode) {
                switch (errorNode->getErrorType()) {
                    case ErrorNode::ErrorType::RIGHT_BRACKET:
                        throw MissingRightBracketException(GramNode::nowLine);
                    default:
                        std::cout << __FILE__ << ':' << __LINE__ << ':' << "Unreachable" << std::endl;
                        return false;
                }
            }
        } catch (MissingRightBracketException &e) {
            e.myOutput();
            return false;
        }
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto left_bracket_p = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (left_bracket_p)
                dimension++;
        }
    }
    try {
        if (!GramNode::getNowTable()->addIdent(*ident_p->getValue_p(),
                                            std::make_shared<IdentInfo>(false, dimension))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (DupIdentException &e) {
        e.myOutput();
        return false;
    }
    return true;
}

bool FuncFParam::addSymTable() {
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    std::string name = *ident_p->getValue_p();
    auto ite = sons.begin();
    ite += 2;
    int dimension = 0;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lbrack_p = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lbrack_p) {
                dimension++;
            }
        }
    }
    try {
        if (!GramNode::getNowTable()->addIdent(name, std::make_shared<IdentInfo>(false, dimension))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (DupIdentException &e) {
        e.myOutput();
        return false;
    }
    return true;
}

std::pair<std::string, std::shared_ptr<IdentInfo>> FuncFParam::getParamType() {
    std::pair<std::string, std::shared_ptr<IdentInfo>> toReturn;
    std::shared_ptr<TokenNode> tokenNode_p = std::dynamic_pointer_cast<TokenNode>(sons[1]);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    auto ite = sons.begin();
    int dimension = 0;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lbrack_p = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lbrack_p) {
                dimension++;
            }
        }
    }
    toReturn = std::make_pair(*ident_p->getValue_p(), std::make_shared<IdentInfo>(false, dimension));
    return toReturn;
}



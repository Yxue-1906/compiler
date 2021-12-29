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
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_BRACKET);
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
    auto ite = sons.begin() + 1;
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    int dimension = 0;
    ++ite;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lb = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lb)
                dimension++;
        } else if (!(*ite)->checkValid()) {
            return false;
        }
    }
    this->ident = ident_p;
    this->type = std::make_shared<IdentInfo>(false, dimension);
    return true;
}

bool FuncFParam::getParamType(std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>> &toReturn) {
    if (!this->type)
        return false;
    toReturn = std::make_pair(this->ident, this->type);
    return true;
}

std::pair<std::string, std::string> FuncFParam::getParam() {
    std::pair<std::string, std::string> toReturn;
    auto ite = sons.begin() + 1;
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    ++ite;
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
    toReturn.first = *ident_p;
    auto dimension_p = std::make_shared<std::vector<int>>();
    std::shared_ptr<ConstExp> constExp_p;
    for (; ite < sons.end();) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::LBRACK) {
                ++ite;
                constExp_p = std::dynamic_pointer_cast<ConstExp>(*ite);
                if (constExp_p) {
                    int toPush = constExp_p->toValue();
                    dimension_p->push_back(toPush);
                    ite += 2;
                } else {
                    dimension_p->push_back(0);
                    ite++;
                }
            } else {
                //should not happen;
                int tmp;
                std::cout << "error occured here" << std::endl;
                std::cin >> tmp;
            }
        }
    }
    symTableGenCode.addVar(*ident_p, dimension_p);
    auto varInfo = symTableGenCode.searchVar(*ident_p);
    if (dimension_p->empty()) {
        toReturn.second = varInfo->tmpName;
    } else {
        toReturn.second = "&" + varInfo->tmpName;
    }
    return toReturn;
}
/*
std::vector<std::shared_ptr<std::string>> FuncFParam::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    auto ite = sons.begin() + 1;
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    ++ite;
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
    auto dimension_p = std::make_shared<std::vector<int>>();
    std::shared_ptr<ConstExp> constExp_p;
    for (; ite < sons.end();) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::LBRACK) {
                ++ite;
                constExp_p = std::dynamic_pointer_cast<ConstExp>(*ite);
                if (constExp_p) {
                    int toPush = constExp_p->toValue();
                    dimension_p->push_back(toPush);
                    ite += 2;
                } else {
                    dimension_p->push_back(0);
                    ite++;
                }
            } else {
                //should not happen;
                int tmp;
                std::cout << "error occured here" << std::endl;
                std::cin >> tmp;
            }
        }
    }
    symTableGenCode.addVar(*ident_p, dimension_p);
    if (dimension_p->empty()) {
        toReturn.push_back(ident_p);
    } else {
        toReturn.push_back(std::make_shared<std::string>("&" + *ident_p));
    }
    return toReturn;
}
*/



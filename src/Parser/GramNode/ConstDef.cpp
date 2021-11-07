//
// Created by unrelated on 2021/10/18.
//

#include "ConstDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "ConstInitVal.h"
#include "../../Lexer/Token/LBRACK.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"

ConstDef::ConstDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("ConstDef");
    setSons(std::move(sons));
}

/**
 * ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
 * @param toAdd
 * @param ite_p
 * @return
 */
bool ConstDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::IDENFR)) {
        return false;
    }
    for (; TokenNode::create(son_ps, ite, TokenBase::LBRACK);) {
        if (!ConstExp::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RBRACK)) {
            return false;
        }
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::ASSIGN)) {
        return false;
    }
    if (!ConstInitVal::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<ConstDef> tmp_p;
    tmp_p.reset(new ConstDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool ConstDef::checkValid() {
    int left = 0;
    for (auto &i: this->sons) {
        i->updateLineNumber();
        auto errorNode = std::dynamic_pointer_cast<ErrorNode>(i);
        if (errorNode) {
            switch (errorNode->errorType) {
                case ErrorNode::ErrorType::RIGHT_BRACKET:
                    throw MissingRightBracketException(GramNode::nowLine);
            }
        }
    }
}

std::shared_ptr<IdentInfo> getType() {
    bool toReturn = true;
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    auto ident_p = std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p());
    std::string name = *ident_p->getValue_p();
    ++ite;
    int dimension = 0, leftCount = 0;
    for (; ite != sons.end(); ++ite) {
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        if (tokenNode_p) {
            auto lbrack_p = std::dynamic_pointer_cast<LBRACK>(tokenNode_p->getToken_p());
            if (lbrack_p) {
                leftCount++;
                dimension++;
            } else {
                leftCount--;
            }
        }
    }

}

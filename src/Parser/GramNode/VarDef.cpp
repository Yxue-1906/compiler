//
// Created by unrelated on 2021/10/18.
//

#include "VarDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "InitVal.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightBracketException.h"
#include "../../Lexer/Token/LBRACK.h"
#include "../../VM/PCode/ALLO.h"
#include "../../VM/PCode/STO.h"

VarDef::VarDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("VarDef");
    setSons(std::move(sons));
}

/**
 * VarDef -> Ident { '[' ConstExp ']' } |
 *           Ident { '[' ConstExp ']' } '=' InitVal
 * @param toAdd
 * @param ite_p
 * @return
 */
bool VarDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
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
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_BRACKET);
        }
    }
    if (TokenNode::create(son_ps, ite, TokenBase::ASSIGN)) {
        if (!InitVal::create(son_ps, ite)) {
            return false;
        }
    }
    ite_p = ite;
    std::shared_ptr<VarDef> tmp_p;
    tmp_p.reset(new VarDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool VarDef::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
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
        } else {
            toReturn &= (*ite)->checkValid();
        }
    }
    try {
        if (!GramNode::getNowTable()->addIdent(*ident_p->getValue_p(), std::make_shared<IdentInfo>(false, dimension))) {
            throw DupIdentException(ident_p->getLineNumber());
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
    return toReturn;
}

std::vector<std::shared_ptr<std::string>> VarDef::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    auto ite = this->sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    ite += 2;
    std::shared_ptr<std::string> ident =
            std::dynamic_pointer_cast<IDENFR>(tokenNode_p->getToken_p())->getValue_p();
    auto dimension_p = std::make_shared<std::vector<int>>();
    for (auto constExp_p = std::dynamic_pointer_cast<ConstExp>(*ite); ite < this->sons.end(); ite += 3) {
        constExp_p = std::dynamic_pointer_cast<ConstExp>(*ite);
        if (!constExp_p)
            break;
        int toPush = constExp_p->toValue();
        dimension_p->push_back(toPush);
    }
    int size = 1;
    for (int i: *dimension_p) {
        size *= i;
    }
    MidCodeSequence.push_back(std::make_shared<INTERPRETER::ALLO>(*ident, size));
    if (ite < this->sons.end() && std::dynamic_pointer_cast<InitVal>(*ite)) {
        auto initVal_p = std::dynamic_pointer_cast<InitVal>(*ite);
        auto initVals_p = initVal_p->toMidCode();
        for (int i = 0; i < initVals_p.size(); ++i) {
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::STO>(*initVals_p[i], *ident, std::to_string(i)));
        }
    }
    return toReturn;
}

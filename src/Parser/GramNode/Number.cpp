//
// Created by unrelated on 2021/10/20.
//

#include "Number.h"
#include "../TokenNode.h"
#include "../../Lexer/Token/INTCON.h"

Number::Number(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("Number");
    setSons(std::move(sons));
}

bool Number::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::INTCON)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<Number> tmp_p;
    tmp_p.reset(new Number(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

int Number::toValue() {
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(this->sons[0]);
    auto intcon_p = std::dynamic_pointer_cast<INTCON>(tokenNode_p->getToken_p());
    int toReturn = *intcon_p->getValue_p();
    return toReturn;
}

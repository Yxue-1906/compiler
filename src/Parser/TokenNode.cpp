//
// Created by unrelated on 2021/10/18.
//

#include "TokenNode.h"

#include <utility>

TokenNode::TokenNode(std::shared_ptr<TokenBase> token_p) : token_p(std::move(token_p)), GramNode() {}

void TokenNode::myOutput() {
    token_p->myOutput();
}

std::shared_ptr<TokenBase> TokenNode::getToken_p() {
    return this->token_p;
}

bool
TokenNode::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, int type) {
    auto ite = ite_p;
    if (TokenBase::isTypeOf(ite, type)) {
#ifdef DEBUG
        std::cerr << (*ite)->getLineNumber() << ':';
        if (dynamic_cast<Token<std::string> * >(*ite)) {
            std::cerr << *dynamic_cast<Token<std::string> *>(*ite)->getValue_p() << std::endl;
        } else {
            std::cerr << *dynamic_cast<Token<int> *>(*ite)->getValue_p() << std::endl;
        }
#endif
        std::shared_ptr<TokenBase> tmp_token_p;
        tmp_token_p.reset(*ite);
        GramNode::nowLine = tmp_token_p->getLineNumber();
        std::shared_ptr<TokenNode> tmp_p;
        tmp_p.reset(new TokenNode(tmp_token_p));
        toAdd.push_back(tmp_p);
        ite_p = ++ite;
        return true;
    }
    return false;
}

bool TokenNode::checkValid() {
    return true;
}

void TokenNode::updateLineNumber() {
    GramNode::nowLine = this->token_p->getLineNumber();
}

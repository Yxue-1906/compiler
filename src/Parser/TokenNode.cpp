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
        std::shared_ptr<TokenBase> tmp_token_p;
        tmp_token_p.reset(*ite);
        std::shared_ptr<TokenNode> tmp_p;
        tmp_p.reset(new TokenNode(tmp_token_p));
        toAdd.push_back(tmp_p);
        ite_p = ++ite;
        return true;
    }
    return false;
}
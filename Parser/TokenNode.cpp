//
// Created by unrelated on 2021/10/18.
//

#include "TokenNode.h"

TokenNode::TokenNode(Token &token) : token(token) {}

void TokenNode::myOutput() {
    token.myOutput();
}

bool TokenNode::create(GramNode *toReturn, std::vector<Token *>::iterator ite_p, int type) {
    auto ite = ite_p;
    if ((**ite).isTypeOf(type)) {
        toReturn = new TokenNode(**ite);
        ite_p = ++ite;
        return true;
    }
    return false;
}
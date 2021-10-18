//
// Created by unrelated on 2021/10/18.
//

#include "TokenNode.h"

TokenNode::TokenNode(Token &token) : token(token) {}

void TokenNode::myOutput() {
    token.myOutput();
}
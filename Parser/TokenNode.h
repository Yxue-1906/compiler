//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_TOKENNODE_H
#define PARSER_TOKENNODE_H


#include "GramNode.h"

class TokenNode : public GramNode {
private:
    Token &token;
public:
    TokenNode(Token &);

private:
public:
    virtual void myOutput() override;
};


#endif //PARSER_TOKENNODE_H

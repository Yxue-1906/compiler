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


private:
    TokenNode(Token &);

public:

    virtual void myOutput() override;

    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator, int);
};


#endif //PARSER_TOKENNODE_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_TOKENNODE_H
#define PARSER_TOKENNODE_H


#include "GramNode.h"

class TokenNode : public GramNode {
private:
    std::shared_ptr<TokenBase> token_p;
public:


private:
    TokenNode(std::shared_ptr<TokenBase>);

public:

    virtual void myOutput() override;

    std::shared_ptr<TokenBase> getToken_p();

    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &, int);
};


#endif //PARSER_TOKENNODE_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTINITVAL_H
#define PARSER_CONSTINITVAL_H


#include "../GramNode.h"

class ConstInitVal : GramNode {
private:
public:
private:
    ConstInitVal(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);
};


#endif //PARSER_CONSTINITVAL_H

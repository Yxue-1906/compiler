//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCFPARAMS_H
#define PARSER_FUNCFPARAMS_H


#include "../GramNode.h"

class FuncFParams : public GramNode {
private:
public:
private:
    FuncFParams(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_FUNCFPARAMS_H

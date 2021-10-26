//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCRPARAMS_H
#define PARSER_FUNCRPARAMS_H


#include "../GramNode.h"

class FuncRParams : public GramNode{
private:
public:
private:
    FuncRParams(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};


#endif //PARSER_FUNCRPARAMS_H

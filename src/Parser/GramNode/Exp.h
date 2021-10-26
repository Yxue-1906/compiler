//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_EXP_H
#define PARSER_EXP_H


#include "../GramNode.h"
#include "LVal.h"

class Exp : GramNode {
private:
public:
private:
    Exp(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &, LVal *);
};


#endif //PARSER_EXP_H

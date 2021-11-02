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
    Exp(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &, LVal *);
};


#endif //PARSER_EXP_H

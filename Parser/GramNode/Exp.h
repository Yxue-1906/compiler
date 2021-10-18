//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_EXP_H
#define PARSER_EXP_H


#include "../GramNode.h"

class Exp : GramNode {
private:
public:
private:
    Exp(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);
};


#endif //PARSER_EXP_H

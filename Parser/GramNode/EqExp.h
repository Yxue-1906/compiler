//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_EQEXP_H
#define PARSER_EQEXP_H


#include "../GramNode.h"

class EqExp : public GramNode {
private:

public:

private:
    EqExp(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);

};


#endif //PARSER_EQEXP_H

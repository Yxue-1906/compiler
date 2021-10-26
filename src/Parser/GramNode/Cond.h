//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_COND_H
#define PARSER_COND_H


#include "../GramNode.h"

class Cond : public GramNode {
private:

public:

private:
    Cond(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};


#endif //PARSER_COND_H

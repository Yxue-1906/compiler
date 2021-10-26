//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_LANDEXP_H
#define PARSER_LANDEXP_H


#include "../GramNode.h"

class LAndExp : public GramNode {
private:

public:

private:
    LAndExp(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};


#endif //PARSER_LANDEXP_H

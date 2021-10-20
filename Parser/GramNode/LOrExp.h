//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_LOREXP_H
#define PARSER_LOREXP_H


#include "../GramNode.h"

class LOrExp : public GramNode {
private:

public:

private:
    LOrExp(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};


#endif //PARSER_LOREXP_H

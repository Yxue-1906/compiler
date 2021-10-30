//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_INITVAL_H
#define PARSER_INITVAL_H

#include "../GramNode.h"


class InitVal : public GramNode {
private:
public:
private:
    InitVal(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_INITVAL_H

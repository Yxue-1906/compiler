//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_LVAL_H
#define PARSER_LVAL_H

#include "../GramNode.h"

class LVal : public GramNode {
private:

public:

private:
    LVal(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_LVAL_H

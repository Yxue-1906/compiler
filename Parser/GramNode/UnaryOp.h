//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_UNARYOP_H
#define PARSER_UNARYOP_H

#include "../GramNode.h"

class UnaryOp : public GramNode {
private:

public:

private:
    UnaryOp(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};

#endif //PARSER_UNARYOP_H
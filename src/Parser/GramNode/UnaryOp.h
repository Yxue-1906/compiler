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
    UnaryOp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};

#endif //PARSER_UNARYOP_H

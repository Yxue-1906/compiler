//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_UNARYEXP_H
#define PARSER_UNARYEXP_H


#include "../GramNode.h"

class UnaryExp : public GramNode {
private:

public:

private:
    UnaryExp(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};

#endif //PARSER_UNARYEXP_H

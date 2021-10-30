//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_ADDEXP_H
#define PARSER_ADDEXP_H


#include "../GramNode.h"

class AddExp : public GramNode {
private:
public:
private:
    AddExp(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);
};


#endif //PARSER_ADDEXP_H

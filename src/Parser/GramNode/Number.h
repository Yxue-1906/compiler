//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_NUMBER_H
#define PARSER_NUMBER_H


#include "../GramNode.h"

class Number : public GramNode {
private:
public:
private:
    Number(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_NUMBER_H

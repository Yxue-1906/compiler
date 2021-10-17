//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_COMPUNIT_H
#define PARSER_COMPUNIT_H


#include "../GramNode.h"

class CompUnit : GramNode {
private:

public:

private:
    CompUnit(std::vector<Token>);

public:
    virtual bool create(std::vector<Token *>::iterator &) override;

};


#endif //PARSER_COMPUNIT_H

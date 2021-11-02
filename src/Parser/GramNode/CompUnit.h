//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_COMPUNIT_H
#define PARSER_COMPUNIT_H


#include "../GramNode.h"

class CompUnit : public GramNode {
private:

public:

private:
    CompUnit(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_COMPUNIT_H

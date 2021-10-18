//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_BTYPE_H
#define PARSER_BTYPE_H


#include "../GramNode.h"

class BType : GramNode {
private:
public:
private:
    BType(std::vector<GramNode>);

public:
    static bool create(GramNode &, std::vector<Token *>::iterator &);
};


#endif //PARSER_BTYPE_H

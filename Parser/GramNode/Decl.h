//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_DECL_H
#define PARSER_DECL_H


#include "../GramNode.h"

class Decl : public GramNode {
private:

public:

private:
    Decl(std::vector<GramNode>);

public:
    static bool create(GramNode *, std::vector<Token *>::iterator *);
};


#endif //PARSER_DECL_H

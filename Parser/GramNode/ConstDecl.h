//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTDECL_H
#define PARSER_CONSTDECL_H


#include "../GramNode.h"


class ConstDecl : public GramNode {
private:
public:
private:
    ConstDecl(std::vector<GramNode *>);

public:
    static bool create(GramNode **, std::vector<Token *>::iterator &);
};


#endif //PARSER_CONSTDECL_H

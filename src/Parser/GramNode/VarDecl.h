//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_VARDECL_H
#define PARSER_VARDECL_H


#include "../GramNode.h"

class VarDecl : public GramNode {
private:
public:
private:
    VarDecl(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);
};


#endif //PARSER_VARDECL_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_FUNCDEF_H
#define PARSER_FUNCDEF_H


#include "../GramNode.h"

class FuncDef : public GramNode {
private:
public:
private:
    FuncDef(std::vector<GramNode *>);

public:
    static bool create(GramNode **, std::vector<Token *>::iterator &);
};


#endif //PARSER_FUNCDEF_H

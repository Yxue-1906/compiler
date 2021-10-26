//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCFPARAM_H
#define PARSER_FUNCFPARAM_H


#include "../GramNode.h"

class FuncFParam : public GramNode {
private:
public:
private:
    FuncFParam(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};


#endif //PARSER_FUNCFPARAM_H

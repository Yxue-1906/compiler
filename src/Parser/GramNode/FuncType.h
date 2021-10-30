//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCTYPE_H
#define PARSER_FUNCTYPE_H


#include "../GramNode.h"

class FuncType : public GramNode {
private:
public:
private:
    FuncType(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_FUNCTYPE_H

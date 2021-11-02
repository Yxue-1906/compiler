//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTINITVAL_H
#define PARSER_CONSTINITVAL_H


#include "../GramNode.h"

class ConstInitVal : public GramNode {
private:
public:
private:
    ConstInitVal(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);
};


#endif //PARSER_CONSTINITVAL_H

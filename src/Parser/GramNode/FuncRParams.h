//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCRPARAMS_H
#define PARSER_FUNCRPARAMS_H


#include "../GramNode.h"

class FuncRParams : public GramNode {
private:
public:
private:
    FuncRParams(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    std::vector<std::shared_ptr<IdentInfo>> getParamTypes(int lineNumber);
};


#endif //PARSER_FUNCRPARAMS_H

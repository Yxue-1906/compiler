//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCFPARAMS_H
#define PARSER_FUNCFPARAMS_H


#include "../GramNode.h"

class FuncFParams : public GramNode {
private:
public:
private:
    FuncFParams(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    bool addSymTable();

    bool getParamTypes(std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> &toReturn);
};


#endif //PARSER_FUNCFPARAMS_H

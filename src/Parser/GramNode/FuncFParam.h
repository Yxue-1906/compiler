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
    FuncFParam(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    bool addSymTable();

    std::pair<std::string, std::shared_ptr<IdentInfo>> getParamType();
};


#endif //PARSER_FUNCFPARAM_H

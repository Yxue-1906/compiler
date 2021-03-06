//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCFPARAMS_H
#define PARSER_FUNCFPARAMS_H


#include "../GramNode.h"

class FuncFParams : public GramNode {
private:
    std::vector<std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>>> params;
public:
private:
    FuncFParams(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    bool getParamTypes(std::vector<std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>>> &toReturn);

    std::shared_ptr<std::vector<std::string>> getParams();
};


#endif //PARSER_FUNCFPARAMS_H

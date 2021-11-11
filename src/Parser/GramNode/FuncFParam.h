//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_FUNCFPARAM_H
#define PARSER_FUNCFPARAM_H


#include "../GramNode.h"

class FuncFParam : public GramNode {
private:
    std::shared_ptr<IDENFR> ident;
    std::shared_ptr<IdentInfo> type;
public:
private:
    FuncFParam(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    bool getParamType(std::pair<std::shared_ptr<IDENFR>, std::shared_ptr<IdentInfo>> &toReturn);
};


#endif //PARSER_FUNCFPARAM_H

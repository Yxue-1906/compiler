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
    FuncType(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    bool getReturnType(std::shared_ptr<IdentInfo> &toReturn);

    virtual bool checkValid() override;
};


#endif //PARSER_FUNCTYPE_H

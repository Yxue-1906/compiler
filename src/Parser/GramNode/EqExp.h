//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_EQEXP_H
#define PARSER_EQEXP_H


#include "../GramNode.h"

class EqExp : public GramNode {
private:

public:

private:
    EqExp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;
};


#endif //PARSER_EQEXP_H

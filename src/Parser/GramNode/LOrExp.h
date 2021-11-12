//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_LOREXP_H
#define PARSER_LOREXP_H


#include "../GramNode.h"

class LOrExp : public GramNode {
private:

public:

private:
    LOrExp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

};


#endif //PARSER_LOREXP_H

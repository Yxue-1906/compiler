//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_COND_H
#define PARSER_COND_H


#include "../GramNode.h"

class Cond : public GramNode {
private:

public:

private:
    Cond(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

};


#endif //PARSER_COND_H

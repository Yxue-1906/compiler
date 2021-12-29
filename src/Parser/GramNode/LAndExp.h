//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_LANDEXP_H
#define PARSER_LANDEXP_H


#include "../GramNode.h"

class LAndExp : public GramNode {
private:

public:

private:
    LAndExp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;
};


#endif //PARSER_LANDEXP_H

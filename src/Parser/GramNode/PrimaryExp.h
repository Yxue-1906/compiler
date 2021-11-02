//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_PRIMARYEXP_H
#define PARSER_PRIMARYEXP_H


#include "../GramNode.h"

class PrimaryExp : public GramNode {
private:
public:
private:
    PrimaryExp(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);
};


#endif //PARSER_PRIMARYEXP_H

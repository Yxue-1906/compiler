//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTEXP_H
#define PARSER_CONSTEXP_H


#include "../GramNode.h"

class ConstExp : public GramNode {
private:
public:
private:
    ConstExp(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);
};


#endif //PARSER_CONSTEXP_H

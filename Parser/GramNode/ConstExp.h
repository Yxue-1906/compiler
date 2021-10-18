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
    ConstExp(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);
};


#endif //PARSER_CONSTEXP_H

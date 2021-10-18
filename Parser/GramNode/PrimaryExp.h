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
    PrimaryExp(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);
};


#endif //PARSER_PRIMARYEXP_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_IDENT_H
#define PARSER_IDENT_H


#include "../GramNode.h"

class Ident : public GramNode {
private:
public:
private:
    Ident(std::vector<GramNode *> sons);

public:
    static bool create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p);
};


#endif //PARSER_IDENT_H

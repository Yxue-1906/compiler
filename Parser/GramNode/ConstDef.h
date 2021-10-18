//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTDEF_H
#define PARSER_CONSTDEF_H


#include "../GramNode.h"

class ConstDef : public GramNode {
private:
public:
private:
    ConstDef(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);
};


#endif //PARSER_CONSTDEF_H

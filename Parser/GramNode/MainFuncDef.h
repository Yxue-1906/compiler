//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_MAINFUNCDEF_H
#define PARSER_MAINFUNCDEF_H


#include "../GramNode.h"

class MainFuncDef : GramNode {
private:

public:

private:
    MainFuncDef(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);
};


#endif //PARSER_MAINFUNCDEF_H

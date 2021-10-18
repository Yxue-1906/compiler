//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_VALDECL_H
#define PARSER_VALDECL_H


#include "../GramNode.h"

class ValDecl : public GramNode {
private:
public:
private:
    ValDecl(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);
};


#endif //PARSER_VALDECL_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_VARDEF_H
#define PARSER_VARDEF_H


#include "../GramNode.h"

class VarDef : public GramNode {
private:
public:
private:
    VarDef(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_VARDEF_H

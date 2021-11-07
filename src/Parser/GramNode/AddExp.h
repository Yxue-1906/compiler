//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_ADDEXP_H
#define PARSER_ADDEXP_H


#include "../GramNode.h"

class AddExp : public GramNode {
private:
public:
private:
    AddExp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    bool getType(std::shared_ptr<IdentInfo> &toReturn);
};


#endif //PARSER_ADDEXP_H

//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_LVAL_H
#define PARSER_LVAL_H

#include "../GramNode.h"

class LVal : public GramNode {
private:

public:

private:
    LVal(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    bool getType(std::shared_ptr<IdentInfo> &toReturn);
};


#endif //PARSER_LVAL_H

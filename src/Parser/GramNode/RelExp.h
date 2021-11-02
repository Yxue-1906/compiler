//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_RELEXP_H
#define PARSER_RELEXP_H

#include "../GramNode.h"


class RelExp : public GramNode {
private:

public:

private:
    RelExp(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_RELEXP_H

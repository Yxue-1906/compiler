//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_MULEXP_H
#define PARSER_MULEXP_H


#include "../GramNode.h"

class MulExp : public GramNode {
private:

public:

private:
    MulExp(std::vector<std::shared_ptr<GramNode>>sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};

#endif //PARSER_MULEXP_H

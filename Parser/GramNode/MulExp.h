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
    MulExp(std::vector<GramNode *>);

public:
    static bool create(GramNode *&, std::vector<Token *>::iterator &);

};

#endif //PARSER_MULEXP_H

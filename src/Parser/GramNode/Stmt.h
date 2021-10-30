//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_STMT_H
#define PARSER_STMT_H

#include "../GramNode.h"


class Stmt : public GramNode {
private:

public:

private:
    Stmt(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_STMT_H

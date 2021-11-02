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
    Stmt(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &, bool isLoop);

    bool getReturnType(std::shared_ptr<IdentInfo> &toReturn);
};


#endif //PARSER_STMT_H

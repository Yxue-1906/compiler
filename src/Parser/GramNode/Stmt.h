//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_STMT_H
#define PARSER_STMT_H

#include "../GramNode.h"


class Stmt : public GramNode {
private:
    const bool isLoop;
    const bool isVoid;
public:

private:
    Stmt(std::vector<std::shared_ptr<GramNode>> sons, bool isLoop, bool isVoid);

    bool isConBreak();

public:
    static bool
    create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop,
           bool isVoid);

    virtual bool checkValid() override;

    bool hasReturn();
};

#endif //PARSER_STMT_H

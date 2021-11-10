//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_STMT_H
#define PARSER_STMT_H

#include "../GramNode.h"


class Stmt : public GramNode {
private:
    const bool isLoop;
public:

private:
    Stmt(std::vector<std::shared_ptr<GramNode>> sons, bool isLoop);

    bool isConBreak();

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &, bool isLoop);

    virtual bool checkValid() override;

    int isNonVoidReturn(bool isVoid);
};

#endif //PARSER_STMT_H

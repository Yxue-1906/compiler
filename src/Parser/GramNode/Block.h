//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_BLOCK_H
#define PARSER_BLOCK_H

#include "../GramNode.h"

class Block : public GramNode {
private:

public:

private:
    Block(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool
    create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &, bool isLoop);

    virtual bool checkValid() override;

    bool checkReturn(bool isVoid);

    int getRightBracketLineNumber();
};


#endif //PARSER_BLOCK_H

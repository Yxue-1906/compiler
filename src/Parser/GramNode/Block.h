//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_BLOCK_H
#define PARSER_BLOCK_H
#include "../GramNode.h"

class Block: public GramNode {
private:

public:

private:
    Block(std::vector<GramNode *>);

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);

};


#endif //PARSER_BLOCK_H

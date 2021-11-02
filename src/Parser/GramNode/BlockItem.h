//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_BLOCKITEM_H
#define PARSER_BLOCKITEM_H

#include "../GramNode.h"

class BlockItem : public GramNode {
private:

public:

private:
    BlockItem(std::vector<std::shared_ptr<GramNode>>sons);

    virtual void myOutput() override;

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

};


#endif //PARSER_BLOCKITEM_H
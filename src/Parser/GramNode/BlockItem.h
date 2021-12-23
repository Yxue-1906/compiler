//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_BLOCKITEM_H
#define PARSER_BLOCKITEM_H

#include "../GramNode.h"
#include "../../SymTable/SymTable.h"

class BlockItem : public GramNode {
private:

public:

private:
    BlockItem(std::vector<std::shared_ptr<GramNode>> sons);

    virtual void myOutput() override;

public:
    static bool
    create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop,
           bool isVoid);

    virtual bool checkValid() override;

    bool hasReturn();

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;
};


#endif //PARSER_BLOCKITEM_H

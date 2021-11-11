//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_ADDEXP_H
#define PARSER_ADDEXP_H


#include "../GramNode.h"

class AddExp : public GramNode {
private:
    std::shared_ptr<IdentInfo> type;
public:
private:
    AddExp(std::vector<std::shared_ptr<GramNode>> sons);

    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &,
                       __attribute__((unused)) int unUsed);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    bool getType(std::shared_ptr<IdentInfo> &toReturn);
};


#endif //PARSER_ADDEXP_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_PRIMARYEXP_H
#define PARSER_PRIMARYEXP_H


#include "../GramNode.h"

class PrimaryExp : public GramNode {
private:
    std::shared_ptr<IdentInfo> type;
public:
private:
    PrimaryExp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    bool getType(std::shared_ptr<IdentInfo> &toReturn);

    bool getLVal(std::shared_ptr<GramNode> &toReturn);

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;//todo:

    int toValue();
};


#endif //PARSER_PRIMARYEXP_H

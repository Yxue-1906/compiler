//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_EXP_H
#define PARSER_EXP_H


#include "../GramNode.h"
#include "LVal.h"

class Exp : public GramNode {
private:
    std::shared_ptr<IdentInfo> type;
public:
private:
    Exp(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &, LVal *);

    virtual bool checkValid() override;

    bool getType(std::shared_ptr<IdentInfo> &toReturn);

    bool getLVal(std::shared_ptr<GramNode> &toReturn);

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;

    int toValue();
};


#endif //PARSER_EXP_H

//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_LVAL_H
#define PARSER_LVAL_H

#include "../GramNode.h"

class LVal : public GramNode {
private:
    std::shared_ptr<IdentInfo> type;
public:

private:
    LVal(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    bool getType(std::shared_ptr<IdentInfo> &toReturn);

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;

    int toValue();
};


#endif //PARSER_LVAL_H

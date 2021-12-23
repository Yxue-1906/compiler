//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_MULEXP_H
#define PARSER_MULEXP_H


#include "../GramNode.h"

class MulExp : public GramNode {
private:
    std::shared_ptr<IdentInfo> type;
public:

private:
    MulExp(std::vector<std::shared_ptr<GramNode>> sons);

    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &,
                       __attribute__((unused)) int unUsed);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    bool getType(std::shared_ptr<IdentInfo> &toReturn);

    bool getLVal(std::shared_ptr<GramNode> &toReturn);

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;

    int toValue();
};

#endif //PARSER_MULEXP_H

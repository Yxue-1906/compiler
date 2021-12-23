//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_INITVAL_H
#define PARSER_INITVAL_H

#include "../GramNode.h"


class InitVal : public GramNode {
private:
public:
private:
    InitVal(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;

};


#endif //PARSER_INITVAL_H

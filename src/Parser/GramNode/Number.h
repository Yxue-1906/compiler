//
// Created by unrelated on 2021/10/20.
//

#ifndef PARSER_NUMBER_H
#define PARSER_NUMBER_H


#include "../GramNode.h"

class Number : public GramNode {
private:
public:
private:
    Number(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    int toValue();

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;
};


#endif //PARSER_NUMBER_H

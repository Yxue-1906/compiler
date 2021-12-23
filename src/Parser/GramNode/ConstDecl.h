//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTDECL_H
#define PARSER_CONSTDECL_H


#include "../GramNode.h"


class ConstDecl : public GramNode {
private:
public:
private:
    ConstDecl(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;
};


#endif //PARSER_CONSTDECL_H

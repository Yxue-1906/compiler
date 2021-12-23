//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_DECL_H
#define PARSER_DECL_H


#include "../GramNode.h"

class Decl : public GramNode {
private:

public:

private:
    Decl(std::vector<std::shared_ptr<GramNode>> sons);

    virtual void myOutput() override;

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override;
};


#endif //PARSER_DECL_H

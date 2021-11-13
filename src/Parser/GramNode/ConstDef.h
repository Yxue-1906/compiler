//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_CONSTDEF_H
#define PARSER_CONSTDEF_H


#include "../GramNode.h"

class ConstDef : public GramNode {
private:
public:
private:
    ConstDef(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;
};


#endif //PARSER_CONSTDEF_H

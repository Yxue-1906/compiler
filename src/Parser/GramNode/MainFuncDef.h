//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_MAINFUNCDEF_H
#define PARSER_MAINFUNCDEF_H


#include "../GramNode.h"

class MainFuncDef : public GramNode {
private:

public:

private:
    MainFuncDef(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    virtual bool checkValid() override;

    virtual std::string toMidCode() override;
};


#endif //PARSER_MAINFUNCDEF_H

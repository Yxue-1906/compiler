//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_VARDECL_H
#define PARSER_VARDECL_H


#include "../GramNode.h"

class VarDecl : public GramNode {
private:
public:
private:
    VarDecl(std::vector<std::shared_ptr<GramNode>> sons);

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &, std::vector<TokenBase *>::iterator &);

    bool checkValid() override;

    bool addIdent();
};


#endif //PARSER_VARDECL_H

//
// Created by unrelated on 2021/10/18.
//

#ifndef PARSER_BTYPE_H
#define PARSER_BTYPE_H


#include "../GramNode.h"
#include "../TokenNode.h"

class BType : public GramNode {
private:
public:
private:
    BType(std::vector<GramNode *>);

    virtual void myOutput() override;

public:
    static bool create(std::vector<GramNode *> &, std::vector<Token *>::iterator &);
};


#endif //PARSER_BTYPE_H

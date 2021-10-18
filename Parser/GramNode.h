//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRAMNODE_H
#define PARSER_GRAMNODE_H


#include <vector>
#include "../Output/MyOutput.h"
#include "../Lexer/Token.h"
#include <utility>
#include "TokenNode.h"

class GramNode : public MyOutput {
private:
    std::string GramName;

protected:
    std::vector<GramNode> sons;
public:

private:

protected:
    GramNode();

    void setGramName(std::string);

    void setSons(std::vector<GramNode>);

    std::string getGramName();

    std::vector<Token> getSons();

public:

    virtual void myOutput() override;
};


#endif //PARSER_GRAMNODE_H

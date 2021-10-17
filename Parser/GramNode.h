//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRAMNODE_H
#define PARSER_GRAMNODE_H


#include <vector>
#include "../Output/MyOutput.h"
#include "../Lexer/Token.h"

class GramNode : public MyOutput {
private:
    std::vector<Token> sons;
    std::string GramName;
public:

private:

protected:
    void setGramName(std::string);

    void setSons(std::vector<Token>);

public:
    virtual bool create(std::vector<Token *>::iterator &) = 0;

    virtual void myOutput() override;
};


#endif //PARSER_GRAMNODE_H

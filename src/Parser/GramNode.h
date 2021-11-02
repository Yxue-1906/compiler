//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRAMNODE_H
#define PARSER_GRAMNODE_H


#include <vector>
#include "../Output/MyOutput.h"
#include "../Lexer/TokenBase.h"
#include <utility>

class GramNode : public MyOutput {
private:
    std::string GramName;

protected:
    std::vector<std::shared_ptr<GramNode>> sons;
public:

private:

protected:
    GramNode();

    void setGramName(std::string);

    void setSons(std::vector<std::shared_ptr<GramNode>>);

    std::string getGramName();

    std::vector<std::shared_ptr<GramNode>> getSons();

public:

    virtual void myOutput() override;
};


#endif //PARSER_GRAMNODE_H

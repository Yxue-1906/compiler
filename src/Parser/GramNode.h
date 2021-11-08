//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRAMNODE_H
#define PARSER_GRAMNODE_H


#include <vector>
#include "../Output/MyOutput.h"
#include "../Lexer/TokenBase.h"
#include "../SymTable/SymTable.h"
#include <utility>

class GramNode : public MyOutput {
private:
    std::string gramName;

protected:
    std::vector<std::shared_ptr<GramNode>> sons;
    static std::shared_ptr<SymTable> nowTable_p;
public:
    static int nowLine;
protected:
    GramNode();

    void setGramName(std::string);

    void setSons(std::vector<std::shared_ptr<GramNode>>);

    std::string &getGramName();

    std::vector<std::shared_ptr<GramNode>> getSons();

    std::shared_ptr<SymTable> getNowTable();


public:
    std::shared_ptr<GramNode> getSonByIndex(int index);

    virtual void myOutput() override;

    virtual bool checkValid();

    virtual void updateLineNumber();
};


#endif //PARSER_GRAMNODE_H

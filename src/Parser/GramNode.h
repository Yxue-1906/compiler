//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRAMNODE_H
#define PARSER_GRAMNODE_H


#include <vector>
#include "../Output/MyOutput.h"
#include "../Lexer/TokenBase.h"
#include "../SymTable/SymTable.h"
#include "../VM/PCode.h"
#include "SymTableGenCode/SymTableGenCode.h"
#include <utility>

class GramNode : public MyOutput {
private:
    std::string gramName;
    static std::shared_ptr<SymTable> nowTable_p;
protected:
    std::vector<std::shared_ptr<GramNode>> sons;
    static SymTableGenCode symTableGenCode;
    static int nowTmpVarCount;

public:
    static int nowLine;
    static std::vector<std::shared_ptr<PCode>> MidCodeSequence;
    static std::map<std::string, int> labels;

protected:
    GramNode();

    void setGramName(std::string);

    void setSons(std::vector<std::shared_ptr<GramNode>>);

    std::string &getGramName();

    std::vector<std::shared_ptr<GramNode>> getSons();

    static void setNowTable(std::shared_ptr<SymTable> newTable);

    static std::shared_ptr<SymTable> getNowTable();

public:
    std::shared_ptr<GramNode> getSonByIndex(int index);

    virtual void myOutput() override;

    virtual bool checkValid();

    virtual void updateLineNumber();

    virtual std::vector<std::shared_ptr<std::string>> toMidCode();
};


#endif //PARSER_GRAMNODE_H

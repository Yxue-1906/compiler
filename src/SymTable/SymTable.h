//
// Created by unrelated on 2021/10/26.
//

#ifndef PARSER_SYMTABLE_H
#define PARSER_SYMTABLE_H


#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "../Exception/DupIdentException.h"


class Type {
private:
    virtual void do_init() = 0;

public:
    virtual bool isEqual(Type &) = 0;
};

class IdentType : public Type {
private:
    virtual void do_init() override {}

public:
    IdentType(std::string name, bool const isArray, int dimension)
            : name(name), isArray(isArray), dimension(dimension) {}

    const std::string &queryName();

    int queryDimension();

    virtual bool isEqual(Type &info) override;

private:
    std::string name;
    int dimension;

public:
    const bool isArray;
};

class FuncType : public Type {
private:
    void do_init() override {}

public:
    FuncType(std::shared_ptr<IdentType> returnType, std::vector<std::shared_ptr<IdentType>> parmTypes)
            : returnType(returnType), parmTypes(std::move(parmTypes)) {}

    virtual bool isEqual(Type &info) override;

public:
    static int VOID_F;
    static int INT_F;
private:
    std::shared_ptr<IdentType> const returnType;
    std::vector<std::shared_ptr<IdentType>> parmTypes;
};

class SymTable {
private:
    std::map<std::string, std::shared_ptr<Type>> symTable;
    std::shared_ptr<SymTable> former = nullptr;

public:
    std::shared_ptr<Type> queryIdent(std::string name) throw();

    void addIdent(std::string name, std::shared_ptr<Type> type) throw(DupIdentException);
};


#endif //PARSER_SYMTABLE_H

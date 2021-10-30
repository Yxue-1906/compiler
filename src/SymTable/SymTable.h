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
#include "../Exception/MyException/DupIdentException.h"
#include "../Exception/MyException/UndefIdentException.h"
#include "../Lexer/Token/IDENFR.h"

class IdentType;

class FuncType;

class Type {
private:
    virtual void do_init() = 0;

public:
    virtual bool check(const std::vector<std::shared_ptr<IdentType>> parm_ps) const = 0;

    virtual bool check(const IdentType &identType) const = 0;

    virtual const Type &getReturnType() const = 0;

};

class IdentType : public Type {
private:
    virtual void do_init() override {}

public:
    IdentType(std::string name, bool const isArray, int dimension)
            : name(name), isArray(isArray), dimension(dimension) {}

    virtual bool check(const std::vector<std::shared_ptr<IdentType>> parm_ps) const override;

    virtual bool check(const IdentType &identType) const override;

    virtual const Type &getReturnType() const override;

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

    virtual bool check(const std::vector<std::shared_ptr<IdentType>> parm_ps) const override;

    virtual bool check(const IdentType &identType) const override;

    virtual const Type &getReturnType() const override;

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
    std::shared_ptr<SymTable> formerTable_p = nullptr;

public:
    SymTable() = default;

    SymTable(const SymTable &) = delete;//forbid copy construct
    SymTable &operator=(const SymTable &) = delete;

    SymTable(const SymTable &&) = delete;//forbid copy construct
    SymTable &operator=(const SymTable &&) = delete;

    ~SymTable() = default;

    std::shared_ptr<Type> queryIdent(const IDENFR &ident) noexcept(false);

    void addIdent(const IDENFR &ident, std::shared_ptr<Type> &type) noexcept(false);

    std::shared_ptr<SymTable> getFormerTable();


};


#endif //PARSER_SYMTABLE_H

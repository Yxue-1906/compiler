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

class Info {
public:
    virtual bool operator==(Info &a) const = 0;

    virtual bool operator==(Info &&a) const = 0;

    virtual bool operator!=(Info &a) const = 0;

    virtual bool operator!=(Info &&a) const = 0;
};

class IdentInfo : public Info {
public:
    bool operator==(Info &a) const override;

    bool operator==(Info &&a) const override;

    bool operator!=(Info &a) const override;

    bool operator!=(Info &&a) const override;

    IdentInfo(bool isConst, int dimension) noexcept;

    bool checkConst() const noexcept;

    int getDimension() const noexcept;

    static bool add(const std::shared_ptr<IdentInfo> &a, const std::shared_ptr<IdentInfo> &b,
                    std::shared_ptr<IdentInfo> &result);

    static bool mult(const std::shared_ptr<IdentInfo> &a, const std::shared_ptr<IdentInfo> &b,
                     std::shared_ptr<IdentInfo> &result);

private:
    const int isConst;
    const int dimension;

};

class FuncInfo : public Info {
public:
    enum ErrorType {
        MISMATCH_PARAM_NUM, MISMATCH_CALL_TYPE, NO_ERROR
    };
    static ErrorType errorNo;
public:
    bool operator==(Info &a) const override;

    bool operator==(Info &&a) const override;

    bool operator!=(Info &a) const override;

    bool operator!=(Info &&a) const override;

    FuncInfo(std::shared_ptr<IdentInfo> identInfo_p,
             std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>>) noexcept;

    bool checkReturnType(std::shared_ptr<IdentInfo> toCheck) const;

    std::shared_ptr<IdentInfo> getReturnType() noexcept;

    bool checkParamTypes(std::vector<std::shared_ptr<IdentInfo>> &toCheck) const;

    static ErrorType getLastError() noexcept;

private:
    bool checkParamTypes(std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> &toCheck) const;

private:
    std::shared_ptr<IdentInfo> returnType;
    std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> params;

};

class SymTable {
private:
    std::map<std::string, std::shared_ptr<Info>> symTable;
    std::shared_ptr<SymTable> formerTable_p = nullptr;

public:
    SymTable(std::shared_ptr<SymTable> formerTable_p);

    SymTable(const SymTable &) = delete;//
    SymTable &operator=(const SymTable &) = delete;//
    SymTable(const SymTable &&) = delete;//
    SymTable &operator=(const SymTable &&) = delete;//
    ~SymTable() = default;

    std::shared_ptr<Info> queryIdent(std::string &name) noexcept;

    bool addIdent(std::string name, std::shared_ptr<Info> info) noexcept;

    std::shared_ptr<SymTable> getFormerTable_p();

};


#endif //PARSER_SYMTABLE_H

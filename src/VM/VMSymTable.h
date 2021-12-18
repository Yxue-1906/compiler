//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_VMSYMTABLE_H
#define VM_VMSYMTABLE_H


#include <map>
#include <queue>
#include <memory>
#include "BaseObject.h"

class Information : public BaseObject {

};

class VarInformation : public Information {
public:
    const int addr;

public:
    VarInformation(int addr) : addr(addr) {}

    virtual std::string to_string() const override {
        return std::string{"at <"} + std::to_string(addr) + '>';
    }
};

class FuncInformation : public Information {
public:
    const int addr;
    const std::vector<std::shared_ptr<VarInformation>> params;

public:
    FuncInformation(int addr, std::vector<std::shared_ptr<VarInformation>> params)
            : addr(addr), params(params) {}

    virtual std::string to_string() const override {
        return std::string{"at <"} + std::to_string(addr) + '>';
    }
};

class VMSymTable : public BaseObject {

};

class VarTable : public VMSymTable {
public:
    std::map<std::string, std::shared_ptr<VarInformation> > var_ps;
    const std::shared_ptr<VarTable> formerTable_p;

public:
    VarTable(std::shared_ptr<VarTable> formerTable_p) : formerTable_p(formerTable_p) {}

    int find(std::string name) const {
        auto var_p = var_ps.find(name);
        if (var_p == var_ps.end())
            if (formerTable_p)
                return formerTable_p->find(name);
            else
                return -1;
        else
            return var_p->second->addr;
    }

    void add(std::string name, int addr) {
        var_ps[name] = std::make_shared<VarInformation>(addr);
    }

    virtual std::string to_string() const override {
        std::string toReturn;
        auto tmp_p = formerTable_p;
        int depth = 0;
        for (; tmp_p != nullptr; tmp_p = tmp_p->formerTable_p)
            depth++;
        toReturn += std::to_string(depth) + ":\n";
        for (auto &i: var_ps) {
            toReturn += std::string{'\t'} + i.first + ':' + i.second->to_string() + '\n';
        }
        return toReturn;
    }
};

class FuncTable : public VMSymTable {
public:
    std::map<std::string, std::shared_ptr<FuncInformation>> func_ps;

    virtual std::string to_string() const override {
        std::string toReturn;
        toReturn += "FuncTable:\n";
        for (auto &i: func_ps) {
            toReturn += std::string{'\t'} + i.first + ':' + i.second->to_string() + '\n';
        }
        return toReturn;
    }
};


#endif //VM_VMSYMTABLE_H

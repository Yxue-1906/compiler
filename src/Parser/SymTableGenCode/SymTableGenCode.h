//
// Created by unrelated on 2021/12/18.
//

#ifndef SRC_PARSER_SYMTABLEGENCODE_H
#define SRC_PARSER_SYMTABLEGENCODE_H

#include <string>
#include <vector>
#include <memory>
#include <map>

class VarTypeGenCode {
public:
    const std::string name;
    std::shared_ptr<std::vector<int>> dimension_p;
    std::shared_ptr<std::vector<int>> values_p;

    VarTypeGenCode(std::string name, std::shared_ptr<std::vector<int>> dimension_p)
            : name(name), dimension_p(dimension_p) {}

    VarTypeGenCode(std::string name, std::shared_ptr<std::vector<int>> dimension_p,
                   std::shared_ptr<std::vector<int>> values_p)
            : name(name), dimension_p(dimension_p), values_p(values_p) {}

};

class FuncTypeGenCode {
public:
    const std::string name;
    std::vector<std::shared_ptr<VarTypeGenCode>> params;

    FuncTypeGenCode(std::string name, std::vector<std::shared_ptr<VarTypeGenCode>> params)
            : name(name), params(params) {}
};

class SymTableGenCode {
public:
    std::vector<std::shared_ptr<std::map<std::string, std::shared_ptr<VarTypeGenCode>>>> varTableStack;
    std::map<std::string, std::shared_ptr<FuncTypeGenCode>> funcTable;

public:
    SymTableGenCode() {
        this->varTableStack.push_back(std::make_shared<std::map<std::string, std::shared_ptr<VarTypeGenCode>>>());
    }

    std::shared_ptr<VarTypeGenCode> searchVar(std::string name) {
        auto ite = this->varTableStack.rbegin();
        for (; ite != this->varTableStack.rend(); ++ite) {
            auto find = (**ite).find(name);
            if (find != (**ite).end()) {
                return find->second;
            }
        }
        return nullptr;
    }

    std::shared_ptr<FuncTypeGenCode> searchFunc(std::string name) {
        auto find = funcTable.find(name);
        if (find != funcTable.end()) {
            return find->second;
        }
        return nullptr;
    }

    void addConst(std::string name, std::shared_ptr<std::vector<int>> dimension_p,
                  std::shared_ptr<std::vector<int>> values_p) {
        this->varTableStack.back()->emplace(name, std::make_shared<VarTypeGenCode>(name, dimension_p, values_p));

    }

    void addVar(std::string name, std::shared_ptr<std::vector<int>> dimension_p) {
        this->varTableStack.back()->emplace(name, std::make_shared<VarTypeGenCode>(name, dimension_p));
    }

    void newStack() {
        this->varTableStack.push_back(std::make_shared<std::map<std::string, std::shared_ptr<VarTypeGenCode>>>());
    }

    void deleteStack() {
        this->varTableStack.pop_back();
    }
};


#endif //SRC_PARSER_SYMTABLEGENCODE_H

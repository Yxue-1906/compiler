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
    const std::string tmpName;
    std::shared_ptr<std::vector<int>> dimension_p;
    std::shared_ptr<std::vector<int>> values_p;

    VarTypeGenCode(std::string name, std::string tmpName, std::shared_ptr<std::vector<int>> dimension_p)
            : name(name), tmpName(tmpName), dimension_p(dimension_p) {}

    VarTypeGenCode(std::string name, std::string tmpName, std::shared_ptr<std::vector<int>> dimension_p,
                   std::shared_ptr<std::vector<int>> values_p)
            : name(name), tmpName(tmpName), dimension_p(dimension_p), values_p(values_p) {}

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
    std::map<std::string, std::shared_ptr<std::vector<std::string>>> funcTable_s;
    int nowTmpVarCount = 0;

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

    std::shared_ptr<std::vector<std::string>> searchFunc_s(std::string name) {
        auto find = funcTable_s.find(name);
        if (find != funcTable_s.end()) {
            return find->second;
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

/*    void addFunc(std::string name, std::vector<std::pair<std::string, std::shared_ptr<std::vector<int>>>> paramInfos) {
        std::vector<std::shared_ptr<VarTypeGenCode>> paramTypes;
        for (auto paramInfoPair: paramInfos) {
            paramTypes.push_back(std::make_shared<VarTypeGenCode>(paramInfoPair.first, paramInfoPair.second));
        }
        funcTable.emplace(name, std::make_shared<FuncTypeGenCode>(name, paramTypes));
    }*/

    void addFunc_s(std::string name, std::shared_ptr<std::vector<std::string>> paramNames_p) {
        funcTable_s.emplace(name, paramNames_p);
    }

    void addConst(std::string name, std::shared_ptr<std::vector<int>> dimension_p,
                  std::shared_ptr<std::vector<int>> values_p) {
        this->varTableStack.back()->emplace(name,
                                            std::make_shared<VarTypeGenCode>(name,
                                                                             "%" + std::to_string(nowTmpVarCount++),
                                                                             dimension_p, values_p));

    }

    void addVar(std::string name, std::shared_ptr<std::vector<int>> dimension_p) {
        this->varTableStack.back()->emplace(name,
                                            std::make_shared<VarTypeGenCode>(name,
                                                                             "%" + std::to_string(nowTmpVarCount++),
                                                                             dimension_p));
    }

    std::shared_ptr<std::string> getNewTmpVarName() {
        return std::make_shared<std::string>("%" + std::to_string(nowTmpVarCount++));
    }

    void newStack() {
        this->varTableStack.push_back(std::make_shared<std::map<std::string, std::shared_ptr<VarTypeGenCode>>>());
    }

    void deleteStack() {
        this->varTableStack.pop_back();
    }
};


#endif //SRC_PARSER_SYMTABLEGENCODE_H

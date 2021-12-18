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
    std::vector<int> dimension;
};

class FuncTypeGenCode {
public:
    const std::string name;
    std::vector<std::shared_ptr<VarTypeGenCode>> params;
};

class SymTableGenCode {
public:
    std::vector<std::shared_ptr<std::map<std::string, std::shared_ptr<VarTypeGenCode>>>> varTableStack;
    std::map<std::string, std::shared_ptr<FuncTypeGenCode>> funcTable;

public:
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
};


#endif //SRC_PARSER_SYMTABLEGENCODE_H

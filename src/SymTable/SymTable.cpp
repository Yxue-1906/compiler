//
// Created by unrelated on 2021/10/26.
//

#include "SymTable.h"

const std::string &IdentType::queryName() {
    return this->name;
}

int IdentType::queryDimension() {
    return this->dimension;
}

bool IdentType::isEqual(Type &info) {
    if (dynamic_cast<IdentType *>(&info)) {
        auto &identInfo = dynamic_cast<IdentType &>(info);
        if (this->name.empty() ||
            identInfo.name.empty()) {
            return this->dimension == identInfo.dimension;
        } else return this->name == identInfo.name && this->dimension == identInfo.dimension;
    } else {
        return false;
    }
}

bool FuncType::isEqual(Type &info) {
    if (dynamic_cast<FuncType *>(&info)) {
        auto &funcInfo = dynamic_cast<FuncType &>(info);
        if (this->name.empty() ||
            funcInfo.name.empty()) {
            return
        }
    }
}

std::shared_ptr<Type> SymTable::queryIdent(std::string name) throw(class UndefIdentException) {
    try {
        return symTable.at(name);
    }catch (std::out_of_range e){
        throw UndefIdentException()
    }
}

std::shared_ptr<SymTable> SymTable::getFormer() {
    return this->former;
}
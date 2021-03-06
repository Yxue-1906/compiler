//
// Created by unrelated on 2021/10/26.
//

#include "SymTable.h"


/**
 * provide pre-generate instances
 */
bool IdentInfo::operator==(Info &a) const {
    try {
        auto identInfo = dynamic_cast<IdentInfo &>(a);
        if (this->dimension == identInfo.dimension)
            return true;
        return false;
    } catch (std::bad_cast &e) {
        std::cout << __FILE__ << ':' << __LINE__ << ':' << e.what() << std::endl;
        return false;
    }
}

bool IdentInfo::operator==(Info &&a) const {
    try {
        auto identInfo = dynamic_cast<IdentInfo &>(a);
        if (this->dimension == identInfo.dimension)
            return true;
        return false;
    } catch (std::bad_cast &e) {
        std::cout << __FILE__ << ':' << __LINE__ << ':' << e.what() << std::endl;
        return false;
    }
}

bool IdentInfo::operator!=(Info &a) const {
    return !(*this == a);
}

bool IdentInfo::operator!=(Info &&a) const {
    return !(*this == a);
}

IdentInfo::IdentInfo(bool isConst, int dimension) noexcept: isConst(isConst), dimension(dimension) {}

bool IdentInfo::checkConst() const noexcept {
    return this->isConst;
}

int IdentInfo::getDimension() const noexcept {
    return this->dimension;
}

bool IdentInfo::add(const std::shared_ptr<IdentInfo> &a, const std::shared_ptr<IdentInfo> &b,
                    std::shared_ptr<IdentInfo> &result) {
    if (a && b && a->dimension == b->dimension)
        result = std::make_shared<IdentInfo>(true, a->dimension);
    else
        return false;
    return true;
}

bool IdentInfo::mult(const std::shared_ptr<IdentInfo> &a, const std::shared_ptr<IdentInfo> &b,
                     std::shared_ptr<IdentInfo> &result) {
    if (a && b && a->dimension == b->dimension)
        result = std::make_shared<IdentInfo>(true, a->dimension);
    else
        return false;
    return true;
}

void IdentInfo::print() const {
    if (isConst)
        std::cout << "const ";
    std::cout << "int";
    for (int i = 0; i < dimension; ++i)
        std::cout << "[]";
}

FuncInfo::ErrorType FuncInfo::errorNo = FuncInfo::ErrorType::NO_ERROR;

bool FuncInfo::operator==(Info &a) const {
    try {
        auto funcInfo = dynamic_cast<FuncInfo &>(a);
        return checkReturnType(funcInfo.returnType) && checkParamTypes(funcInfo.params);
    } catch (std::bad_cast &e) {
        std::cout << __FILE__ << ':' << __LINE__ << ':' << e.what() << std::endl;
        return false;
    }
}

bool FuncInfo::operator==(Info &&a) const {
    try {
        auto funcInfo = dynamic_cast<FuncInfo &>(a);
        return checkReturnType(funcInfo.returnType) && checkParamTypes(funcInfo.params);
    } catch (std::bad_cast &e) {
        std::cout << __FILE__ << ':' << __LINE__ << ':' << e.what() << std::endl;
        return false;
    }
}

bool FuncInfo::operator!=(Info &a) const {
    return !(*this == a);
}

bool FuncInfo::operator!=(Info &&a) const {
    return !(*this == a);
}

FuncInfo::FuncInfo(std::shared_ptr<IdentInfo> identInfo_p,
                   std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> params) noexcept
        : returnType(identInfo_p), params(std::move(params)) {}

/**
 * check return type of itself equal to toCheck
 * @param toCheck
 * @return
 */
bool FuncInfo::checkReturnType(std::shared_ptr<IdentInfo> toCheck) const {
    if (this->returnType)
        return *this->returnType == *toCheck;
    else if (toCheck)
        return false;
    else
        return true;
}

const std::shared_ptr<IdentInfo> &FuncInfo::getReturnType() noexcept {
    return this->returnType;
}

bool FuncInfo::checkParamTypes(std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> &toCheck) const {
    if (this->params.size() != toCheck.size()) {
        return false;
    }
    auto ite_a = this->params.begin();
    auto ite_b = toCheck.begin();
    for (; ite_a != this->params.end() && ite_b != toCheck.end(); ++ite_a, ++ite_b) {
        if (*(*ite_a).second != *(*ite_b).second) {
            return false;
        }
    }
    return true;
}

bool FuncInfo::checkParamTypes(std::vector<std::shared_ptr<IdentInfo>> &toCheck) const {
    if (this->params.size() != toCheck.size()) {
        FuncInfo::errorNo = FuncInfo::ErrorType::MISMATCH_PARAM_NUM;
        return false;
    }
    auto ite_a = this->params.begin();
    auto ite_b = toCheck.begin();
    for (; ite_a != this->params.end() && ite_b != toCheck.end(); ++ite_a, ++ite_b) {
        if (*(*ite_a).second != **ite_b) {
            FuncInfo::errorNo = FuncInfo::ErrorType::MISMATCH_CALL_TYPE;
            return false;
        }
    }
    return true;
}

const std::vector<std::pair<std::string, std::shared_ptr<IdentInfo>>> &FuncInfo::getParams() const {
    return this->params;
}

FuncInfo::ErrorType FuncInfo::getLastError() noexcept {
    ErrorType toReturn = FuncInfo::errorNo;
    errorNo = NO_ERROR;
    return toReturn;
}

void FuncInfo::print() const {
    if (this->returnType)
        this->returnType->print();
    else
        std::cout << "void";
    std::cout << '(';
    for (auto &i: params) {
        std::cout << i.first << ':';
        i.second->print();
        std::cout << ',';
    }
    std::cout << ')';
}

SymTable::SymTable(std::shared_ptr<SymTable> formerTable_p) {
    this->formerTable_p = formerTable_p;
}

std::shared_ptr<IdentInfo> SymTable::queryVar(std::string &name) noexcept {
    try {
        return varTable.at(name);
    } catch (std::out_of_range &e) {
        if (this->formerTable_p)
            return this->formerTable_p->queryVar(name);
        return nullptr;
    }
}

std::shared_ptr<FuncInfo> SymTable::queryFunc(std::string &name) noexcept {
    try {
        return funcTable.at(name);
    } catch (std::out_of_range &e) {
        if (this->formerTable_p)
            return this->formerTable_p->queryFunc(name);
        return nullptr;
    }
}

std::shared_ptr<SymTable> SymTable::getFormerTable_p() {
    return this->formerTable_p;
}

bool SymTable::addIdent(std::string name, std::shared_ptr<Info> info) noexcept {
    try {
        if (std::dynamic_pointer_cast<IdentInfo>(info)) {
            varTable.at(name);
            varTable[name] = std::dynamic_pointer_cast<IdentInfo>(info);
            return false;
        } else {
            funcTable.at(name);
            funcTable[name] = std::dynamic_pointer_cast<FuncInfo>(info);
            return false;
        }
    } catch (std::out_of_range &e) {
        if (std::dynamic_pointer_cast<IdentInfo>(info)) {
            varTable[name] = std::dynamic_pointer_cast<IdentInfo>(info);
        } else {
            funcTable[name] = std::dynamic_pointer_cast<FuncInfo>(info);
        }
        return true;
    }
}


#ifdef DEBUG

int SymTable::printTable() {
    int tabs = 0;
    if (this->formerTable_p) {
        tabs = this->formerTable_p->printTable();
    }
    for (int j = 0; j < tabs; ++j)
        std::cout << '\t';
    std::cout << '|' << std::endl;
    for (auto &i: this->varTable) {
        for (int j = 0; j < tabs; ++j)
            std::cout << '\t';
        std::cout << i.first << ':';
        i.second->print();
        std::cout << std::endl;
    }
    return tabs + 1;
}

#endif




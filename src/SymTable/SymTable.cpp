//
// Created by unrelated on 2021/10/26.
//

#include "SymTable.h"


/**
 * provide pre-generate instances
 */
std::shared_ptr<IdentInfo>IdentInfo::VARIABLE{new IdentInfo(0)};
std::shared_ptr<IdentInfo>IdentInfo::ARRAY{new IdentInfo(1)};
std::shared_ptr<IdentInfo>IdentInfo::ARRAY_2D{new IdentInfo(2)};

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

IdentInfo::IdentInfo(int dimension) noexcept: dimension(dimension) {}

int FuncInfo::ErrorType = 0;

bool FuncInfo::operator==(Info &a) const {
    try {
        auto funcInfo = dynamic_cast<FuncInfo &>(a);
        return checkReturnType(funcInfo.returnType) && checkParamTypes(funcInfo.parmTypes);
    } catch (std::bad_cast &e) {
        std::cout << __FILE__ << ':' << __LINE__ << ':' << e.what() << std::endl;
        return false;
    }
}

bool FuncInfo::operator==(Info &&a) const {
    try {
        auto funcInfo = dynamic_cast<FuncInfo &>(a);
        return checkReturnType(funcInfo.returnType) && checkParamTypes(funcInfo.parmTypes);
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
                   std::vector<std::shared_ptr<IdentInfo>> parmTypes) noexcept
        : returnType(identInfo_p), parmTypes(std::move(parmTypes)) {}

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

std::shared_ptr<IdentInfo> FuncInfo::getReturnType() noexcept {
    return this->returnType;
}

bool FuncInfo::checkParamTypes(std::vector<std::shared_ptr<IdentInfo>> &toCheck) const {
    if (this->parmTypes.size() != toCheck.size()) {
        FuncInfo::ErrorType = 1;
        return false;
    }
    auto ite_a = this->parmTypes.begin();
    auto ite_b = toCheck.begin();
    for (; ite_a != this->parmTypes.end() && ite_b != toCheck.end(); ++ite_a, ++ite_b) {
        if (**ite_a != **ite_b) {
            FuncInfo::ErrorType = 2;
            return false;
        }
    }
    return true;
}

int FuncInfo::getLastError() const noexcept {
    int toReturn = FuncInfo::ErrorType;
    FuncInfo::ErrorType = 0;
    return toReturn;
}


SymTable::SymTable(std::shared_ptr<SymTable> formerTable_p) {
    this->formerTable_p = formerTable_p;
}

std::shared_ptr<Info> SymTable::queryIdent(std::string &name) noexcept {
    try {
        return symTable.at(name);
    } catch (std::out_of_range &e) {
        return nullptr;
    }
}

std::shared_ptr<SymTable> SymTable::getFormerTable_p() {
    return this->formerTable_p;
}

bool SymTable::addIdent(std::string name, std::shared_ptr<Info> info) noexcept {
    try {
        symTable.at(name);
        return false;
    } catch (std::out_of_range &e) {
        symTable[name] = info;
        return true;
    }
}





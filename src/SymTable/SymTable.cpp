//
// Created by unrelated on 2021/10/26.
//

#include "SymTable.h"


std::shared_ptr<Type> SymTable::queryIdent(const IDENFR &ident) noexcept(false) {
    try {
        return symTable.at(*ident.getValue_p());
    }
    catch (std::out_of_range &e) {
        throw UndefIdentException(ident.getLineNumber(), *ident.getValue_p());
    }
}

std::shared_ptr<SymTable> SymTable::getFormerTable() {
    return this->formerTable_p;
}

void SymTable::addIdent(const IDENFR &ident, std::shared_ptr<Type> &type) noexcept(false) {
    try {
        this->symTable.at(*ident.getValue_p());
        throw DupIdentException(ident.getLineNumber());
    } catch (std::out_of_range &e) {
        this->symTable[*ident.getValue_p()] = type;
    }
}

bool IdentType::check(const std::vector<std::shared_ptr<IdentType>> parm_ps) const {
    return false;
}

bool IdentType::check(const IdentType &identType) const {
    if (this->dimension == identType.dimension)
        return true;
    return false;
}

const Type &IdentType::getReturnType() const {
    return *this;
}

bool FuncType::check(const std::vector<std::shared_ptr<IdentType>> parm_ps) const {
    auto ite_a = this->parmTypes.begin();
    auto ite_b = parm_ps.begin();
    for (; ite_a != this->parmTypes.end() && ite_b != parm_ps.end(); ++ite_a, ++ite_b) {
        if (!(*ite_a)->check(**ite_b))return false;
    }
    return true;
}

bool FuncType::check(const IdentType &identType) const {
    return false;
}

const Type &FuncType::getReturnType() const {
    return *this->returnType;
}

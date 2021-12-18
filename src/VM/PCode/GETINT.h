//
// Created by unrelated on 2021/11/23.
//

#ifndef VM_GETINT_H
#define VM_GETINT_H

#include "../PCode.h"

class GETINT : public PCode {
public:
    const Type type;
    const std::string addr;

public:
    GETINT(std::string addr) : type(Type::GETINT), addr(addr) {}

    virtual std::string to_string() const override {
        return std::string{"GETINT "} + addr;
    }
};


#endif //VM_GETINT_H

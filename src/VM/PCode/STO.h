//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_STO_H
#define VM_STO_H

#include "../PCode.h"

class STO : public PCode {
public:
    const Type type;
    const std::string value;
    const std::string addr;

public:
    STO(std::string value, std::string addr) : type(Type::STO), value(value), addr(addr) {}

    virtual std::string to_string() const override {
        return std::string{"STO "} + value + ' ' + addr;
    }

};


#endif //VM_STO_H

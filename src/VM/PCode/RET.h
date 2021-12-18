//
// Created by unrelated on 2021/11/22.
//

#ifndef VM_RET_H
#define VM_RET_H

#include "../PCode.h"

class RET : public PCode {
public:
    const Type type;
    const std::string name;

public:
    RET(std::string name) : type(Type::RET), name(name) {}

    virtual std::string to_string() const override {
        return std::string{"RET"};
    }
};


#endif //VM_RET_H

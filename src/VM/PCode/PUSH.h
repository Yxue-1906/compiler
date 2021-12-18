//
// Created by unrelated on 2021/11/23.
//

#ifndef VM_PUSH_H
#define VM_PUSH_H

#include "../PCode.h"

class PUSH : public PCode {
public:
    const Type type;
    const std::string name;

public:
    PUSH(std::string name) : type(Type::PUSH), name(name) {}

    virtual std::string to_string() const override {
        return std::string{"PUSH "} + name;
    }
};


#endif //VM_PUSH_H

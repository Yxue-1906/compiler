//
// Created by unrelated on 2021/11/23.
//

#ifndef VM_BR_H
#define VM_BR_H

#include "../PCode.h"

class BR : public PCode {
public:
    const Type type;
    const std::string label1;
    const std::string label2;

public:
    BR(std::string label1, std::string label2) : type(Type::BR), label1(label1), label2(label2) {}

    virtual std::string to_string() const override {
        return std::string{"BR "} + label1 + ' ' + label2;
    }
};


#endif //VM_BR_H

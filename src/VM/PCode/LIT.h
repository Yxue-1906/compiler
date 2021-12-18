//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_LIT_H
#define VM_LIT_H

#include "../PCode.h"

class LIT : public PCode {
public:
    const Type type;
    const int instantValue;

public:
    LIT(int instantValue)
            : type(Type::LIT), instantValue(instantValue) {}

    virtual std::string to_string() const override {
        return std::string{"LIT "} + std::to_string(instantValue);
    }
};


#endif //VM_LIT_H

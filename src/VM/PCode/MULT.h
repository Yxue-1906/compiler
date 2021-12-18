//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_MULT_H
#define VM_MULT_H

#include "../PCode.h"

class MULT : public PCode {
public:
    const Type type;
    const std::string name1;
    const std::string name2;
    const std::string toStore;

public:
    MULT(std::string name1, std::string name2, std::string toStore)
            : type(Type::MULT), name1(name1), name2(name2), toStore(toStore) {}

    virtual std::string to_string() const override {
        return std::string{"MULT "} + name1 + ' ' + name2 + ' ' + toStore;
    }
};


#endif //VM_MULT_H

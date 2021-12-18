//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_MOD_H
#define VM_MOD_H

#include "../PCode.h"

class MOD : public PCode {
public:
    const Type type;
    const std::string name1;
    const std::string name2;
    const std::string toStore;

public:
    MOD(std::string name1, std::string name2, std::string toStore)
            : type(Type::MOD), name1(name1), name2(name2), toStore(toStore) {}

    virtual std::string to_string() const override {
        return std::string{"MOD "} + name1 + ' ' + name2 + ' ' + toStore;
    }
};


#endif //VM_MOD_H

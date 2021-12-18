//
// Created by unrelated on 2021/11/24.
//

#ifndef VM_LODA_H
#define VM_LODA_H

#include "../PCode.h"

class LODA : public PCode {
public:
    const Type type;
    const std::string toStore;
    const std::string from;

public:
    LODA(std::string toStore, std::string from)
            : type(Type::LODA), toStore(toStore), from(from) {}

    virtual std::string to_string() const override {
        return std::string{"LODA *"} + from + "->" + toStore;
    }
};


#endif //VM_LODA_H

//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_LOD_H
#define VM_LOD_H

#include "../PCode.h"

class LOD : public PCode {
public:
    const Type type;
    const std::string toStore;
    const std::string from;

public:
    LOD(std::string to, std::string from)
            : type(Type::LOD), toStore(to), from(from) {}

    virtual std::string to_string() const override {
        return std::string{"LOD "} + from + "->" + toStore;
    }
};


#endif //VM_LOD_H

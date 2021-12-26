//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_LOD_H
#define VM_LOD_H

#include "../PCode.h"

namespace INTERPRETER {
    class LOD : public PCode {
    public:
        const Type type;
        const std::string toStore;
        const std::string from;
        const std::string offset;

    public:
        LOD(std::string toStore, std::string from, std::string offset)
                : type(Type::LOD), toStore(toStore), from(from), offset(offset) {}

        virtual std::string to_string() const override {
            return std::string{"LOD "} + from + '[' + offset + ']' + "->" + toStore;
        }
    };
}


#endif //VM_LOD_H

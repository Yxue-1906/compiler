//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_STO_H
#define VM_STO_H

#include "../PCode.h"

namespace INTERPRETER {
    class STO : public PCode {
    public:
        const Type type;
        const std::string value;
        const std::string base;
        const std::string offset;

    public:
        STO(std::string value, std::string base, std::string offset)
                : type(Type::STO), value(value), base(base), offset(offset) {}

        virtual std::string to_string() const override {
            return std::string{"STO "} + value + "->" + base + '[' + offset + ']';
        }

    };
}


#endif //VM_STO_H

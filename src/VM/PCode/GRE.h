//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_GRE_H
#define VM_GRE_H

#include "../PCode.h"

namespace INTERPRETER {
    class GRE : public PCode {
    public:
        const Type type;
        const std::string left;
        const std::string right;
        const std::string toStore;

    public:
        GRE(std::string left, std::string right, std::string toStore)
                : type(Type::GRE), left(left), right(right), toStore(toStore) {}

        virtual std::string to_string() const override {
            return std::string{"GRE "} + left + ' ' + right + ' ' + toStore;
        }
    };
}


#endif //VM_GRE_H

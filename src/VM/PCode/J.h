//
// Created by unrelated on 2021/11/24.
//

#ifndef VM_J_H
#define VM_J_H

#include "../PCode.h"

namespace INTERPRETER {
    class J : public PCode {
    public:
        const Type type;
        const std::string label;
    public:
        J(std::string label) : type(Type::J), label(label) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return std::string{"J "} + label;
        }
    };
}


#endif //VM_J_H

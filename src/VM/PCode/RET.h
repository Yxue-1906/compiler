//
// Created by unrelated on 2021/11/22.
//

#ifndef VM_RET_H
#define VM_RET_H

#include "../PCode.h"

namespace INTERPRETER {
    class RET : public PCode {
    public:
        const Type type;

    public:
        RET() : type(Type::RET) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return "RET";
        }
    };
}


#endif //VM_RET_H

//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_PWRAP_H
#define VM_PWRAP_H

#include "../PCode.h"

namespace INTERPRETER {
    class PWRAP : public PCode {
    public:
        const Type type;
    public:
        PWRAP() : type(Type::PWRAP) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return std::string{"PWARP"};
        }
    };
}


#endif //VM_PWRAP_H

//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_PINT_H
#define VM_PINT_H

#include "../PCode.h"

namespace INTERPRETER {
    class PINT : public PCode {
    public:
        Type type;
        const std::string name;

    public:
        PINT(std::string name) : type(Type::PINT), name(name) {}

        virtual std::string to_string() const {
            return std::string{"PINT"};
        }
    };
}


#endif //VM_PINT_H

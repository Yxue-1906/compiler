//
// Created by unrelated on 2021/11/23.
//

#ifndef VM_ALLO_H
#define VM_ALLO_H

#include "../PCode.h"

namespace INTERPRETER {
    class ALLO : public PCode {
    public:
        const Type type;
        const std::string name;
        const int size;

    public:
        ALLO(std::string name, int size) : type(Type::ALLO), name(name), size(size) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return std::string{"ALLO "} + name + ' ' + std::to_string(size);
        }
    };
}


#endif //VM_ALLO_H

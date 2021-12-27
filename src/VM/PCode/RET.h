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
        const std::string name;

    public:
        RET(std::string name) : type(Type::RET), name(name) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            int value, addr;
            std::string toReturn = "RET ";
            if (name != "void") {
                addr = varTable_p->find(name);
                if (addr != -1) {
                    value = DataStack[addr];
                    toReturn += name + "(" + std::to_string(value) + ")";
                } else {
                    toReturn += name;
                }
            }
            return toReturn;
        }
    };
}


#endif //VM_RET_H

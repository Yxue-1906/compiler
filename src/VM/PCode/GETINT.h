//
// Created by unrelated on 2021/11/23.
//

#ifndef VM_GETINT_H
#define VM_GETINT_H

#include "../PCode.h"

namespace INTERPRETER {
    class GETINT : public PCode {
    public:
        const Type type;
        const std::string base;
        const std::string offset;

    public:
        GETINT(std::string base, std::string offset)
                : type(Type::GETINT), base(base), offset(offset) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "GETINT ";
            int varBase, varOffset, addr;
            toReturn += " -> ";
            addr = varTable_p->find(base);
            if (addr != -1) {
                varBase = addr;
            } else {
                varBase = std::stoi(base);
            }
            toReturn += base;
            addr = varTable_p->find(offset);
            if (addr != -1) {
                varOffset = DataStack[addr];
                toReturn += "[" + offset + ":" + std::to_string(varOffset) + "]";
            } else {
                toReturn += "[" + offset + "]";
            }
            return toReturn;
        }

    };
}


#endif //VM_GETINT_H

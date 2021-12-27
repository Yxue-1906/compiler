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

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "STO ";
            int varBase, varOffset, addr;
            addr = varTable_p->find(value);
            if (addr != -1) {
                int varValue;
                varValue = DataStack[addr];
                toReturn += value + "(" + std::to_string(varValue) + ")";
            } else {
                toReturn += value;
            }
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


#endif //VM_STO_H

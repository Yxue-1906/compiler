//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_LOD_H
#define VM_LOD_H

#include "../PCode.h"

namespace INTERPRETER {
    class LOD : public PCode {
    public:
        const Type type;
        const std::string toStore;
        const std::string from;
        const std::string offset;

    public:
        LOD(std::string toStore, std::string from, std::string offset)
                : type(Type::LOD), toStore(toStore), from(from), offset(offset) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "LOD ";
            int varFrom, varOffset, addr;
            addr = varTable_p->find(from);
            if (addr != -1) {
                varFrom = addr;
            } else {
                varFrom = std::stoi(from);
            }
            toReturn += from;
            addr = varTable_p->find(offset);
            if (addr != -1) {
                varOffset = DataStack[addr];
                toReturn += "[" + offset + ":" + std::to_string(varOffset) + "]";
            } else {
                varOffset = std::stoi(offset);
                toReturn += "[" + offset + "]";
            }
            toReturn += "(" + std::to_string(DataStack[varFrom + varOffset]) + ")";
            toReturn += " -> ";
            toReturn += toStore;
            return toReturn;
        }
    };
}


#endif //VM_LOD_H

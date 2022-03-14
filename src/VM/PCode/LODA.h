//
// Created by unrelated on 2021/11/24.
//

#ifndef VM_LODA_H
#define VM_LODA_H

#include "../PCode.h"

namespace INTERPRETER {
    class LODA : public PCode {
    public:
        const Type type;
        const std::string toStore;
        const std::string from;
        const std::string offset;

    public:
        LODA(std::string toStore, std::string from, std::string offset)
                : type(Type::LODA), toStore(toStore), from(from), offset(offset) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "LOAD ";
            int addrFrom, varOffset, addr;
            addr = varTable_p->find(from);
            if (addr != -1) {
                addrFrom = addr;
            } else {
                //should not here
                int tmp;
                std::cout << "cant find " << from << std::endl;
//                std::cin >> tmp;
            }
            toReturn += "&" + from;
            addr = varTable_p->find(offset);
            if (addr != -1) {
                varOffset = DataStack[addr];
                toReturn += "[" + offset + ":" + std::to_string(varOffset) + "]";
            } else {
                varOffset = std::stoi(offset);
                toReturn += offset;
            }
            toReturn += "(" + std::to_string(addrFrom + varOffset) + ")";
            toReturn += " -> " + toStore;
            return toReturn;
        }
    };
}


#endif //VM_LODA_H

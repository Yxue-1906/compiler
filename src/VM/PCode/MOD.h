//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_MOD_H
#define VM_MOD_H

#include "../PCode.h"

namespace INTERPRETER {
    class MOD : public PCode {
    public:
        const Type type;
        const std::string name1;
        const std::string name2;
        const std::string toStore;

    public:
        MOD(std::string name1, std::string name2, std::string toStore)
                : type(Type::MOD), name1(name1), name2(name2), toStore(toStore) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "MOD ";
            int addr;
            addr = varTable_p->find(name1);
            if (addr != -1) {
                int var1;
                var1 = DataStack[addr];
                toReturn += name1 + ":" + std::to_string(var1);
            } else {
                toReturn += name1;
            }
            toReturn += " % ";
            addr = varTable_p->find(name2);
            if (addr != -1) {
                int var2;
                var2 = DataStack[addr];
                toReturn += name2 + ":" + std::to_string(var2);
            } else {
                toReturn += name2;
            }
            toReturn += " -> " + toStore;
            return toReturn;
        }
    };
}


#endif //VM_MOD_H

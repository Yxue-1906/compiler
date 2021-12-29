//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_LEQ_H
#define VM_LEQ_H

#include "../PCode.h"

namespace INTERPRETER {
    class LEQ : public PCode {
    public:
        const Type type;
        const std::string left;
        const std::string right;
        const std::string toStore;

    public:
        LEQ(std::string left, std::string right, std::string toStore)
                : type(Type::LEQ), left(left), right(right), toStore(toStore) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "LEQ ";
            int addr;
            addr = varTable_p->find(left);
            if (addr != -1) {
                int leftVar = DataStack[addr];
                toReturn += left + ":" + std::to_string(leftVar);
            } else {
                toReturn += left;
            }
            toReturn += " <= ";
            addr = varTable_p->find(right);
            if (addr != -1) {
                int rightVar = DataStack[addr];
                toReturn += right + ":" + std::to_string(rightVar);
            } else {
                toReturn += right;
            }
            toReturn += " -> " + toStore;
            return toReturn;
        }
    };
}


#endif //VM_LEQ_H

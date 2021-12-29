//
// Created by unrelated on 2021/11/23.
//

#ifndef VM_BR_H
#define VM_BR_H

#include "../PCode.h"

namespace INTERPRETER {
    class BRT : public PCode {
    public:
        const Type type;
        const std::string judge;
        std::string label;

    public:
        BRT(std::string judge)
                : type(Type::BRT), judge(judge) {}

        void setLabel(std::string label) {
            this->label = std::move(label);
        }

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "BRT ";
            int value, addr;
            addr = varTable_p->find(judge);
            if (addr != -1) {
                value = DataStack[addr];
                toReturn += judge + ":" + std::to_string(value);
            } else {
                value = std::stoi(judge);
                toReturn += judge;
            }
            if (!value) {
                toReturn += " \\/ ";
            } else {
                toReturn += " -> " + label;
            }
            return toReturn;
        }
    };
}


#endif //VM_BR_H

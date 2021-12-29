//
// Created by unrelated on 2021/12/29.
//

#ifndef SRC_PARSER_BRF_H
#define SRC_PARSER_BRF_H


#include "../PCode.h"

namespace INTERPRETER {
    class BRF : public PCode {
    public:
        const Type type;
        const std::string judge;
        std::string label;

    public:
        BRF(std::string judge)
                : type(Type::BRT), judge(judge) {}

        void setLabel(std::string label) {
            this->label = std::move(label);
        }

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "BRF ";
            int value, addr;
            addr = varTable_p->find(judge);
            if (addr != -1) {
                value = DataStack[addr];
                toReturn += judge + ":" + std::to_string(value);
            } else {
                value = std::stoi(judge);
                toReturn += judge;
            }
            if (value) {
                toReturn += " \\/ ";
            } else {
                toReturn += " -> " + label;
            }
            return toReturn;
        }
    };
}


#endif //SRC_PARSER_BRF_H

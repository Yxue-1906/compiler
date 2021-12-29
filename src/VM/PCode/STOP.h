//
// Created by unrelated on 2021/12/22.
//

#ifndef SRC_PARSER_STOP_H
#define SRC_PARSER_STOP_H

#include "../PCode.h"

namespace INTERPRETER {
    class STOP : public PCode {
    public:
        const Type type;
        const std::string value;
        const std::string base;
        const std::string offset;

    public:
        STOP(std::string value, std::string base, std::string offset)
                : type(Type::STOP), value(value), base(base), offset(offset) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "STOP ";
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
                varBase = DataStack[addr];
            } else {
                //should not use instant number or just do not find ?
                int tmp;
                std::cout << "error occurred when processing STOP" << std::endl;
                std::cin >> tmp;
            }
            toReturn += "*";
            addr = varTable_p->find(offset);
            if (addr != -1) {
                varOffset = DataStack[addr];
                toReturn += "*(" + base + ":" + std::to_string(varBase) + " + " +
                            offset + ":" + std::to_string(varOffset) + ")";
            } else {
                if (offset != "0") {
                    toReturn += "*(" + base + ":" + std::to_string(varBase) + " + " + offset + ")";
                } else {
                    toReturn += "*" + base + ":" + std::to_string(varBase);
                }
            }
            return toReturn;
        }
    };
}


#endif //SRC_PARSER_STOP_H

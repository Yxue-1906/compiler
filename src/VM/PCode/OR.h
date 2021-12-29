//
// Created by unrelated on 2021/12/29.
//

#ifndef SRC_PARSER_OR_H
#define SRC_PARSER_OR_H

#include "../PCode.h"

namespace INTERPRETER {
    class OR : public PCode {
    public:
        const Type type;
        const std::string name1;
        const std::string name2;
        const std::string toStore;

    public:
        OR(std::string name1, std::string name2, std::string toStore)
                : type(Type::OR), name1(name1), name2(name2), toStore(toStore) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "OR ";
            int addr;
            addr = varTable_p->find(name1);
            if (addr != -1) {
                int var1;
                var1 = DataStack[addr];
                toReturn += name1 + ":" + std::to_string(var1);
            } else {
                toReturn += name1;
            }
            toReturn += " || ";
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


#endif //SRC_PARSER_OR_H

//
// Created by unrelated on 2021/11/22.
//

#ifndef VM_CALL_H
#define VM_CALL_H

#include "../PCode.h"

namespace INTERPRETER {
    class CALL : public PCode {
    public:
        const Type type;
//    const std::string name;
        const std::string funcName;
        std::vector<std::string> inParams;
        std::vector<std::string> formalParams;
    public:
        CALL(std::string funcName) : type(Type::CALL), funcName(funcName) {}

        CALL(std::string funcName, std::vector<std::string> inParams, std::vector<std::string> formalParams)
                : type(Type::CALL),
                  funcName(funcName),
                  inParams(std::move(inParams)),
                  formalParams(std::move(formalParams)) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toReturn = "CALL " + funcName + " ";
            for (int i = 0; i < inParams.size(); ++i) {
                int value;
                value = varTable_p->find(inParams[i]);
                if (value != -1) {
                    value = DataStack[value];
                    toReturn += inParams[i] + ":" + std::to_string(value);
                } else {
                    toReturn += inParams[i];
                }
                toReturn += "->";
                toReturn += formalParams[i];
                toReturn += " ";
            }
            return toReturn;
        }
    };
}


#endif //VM_CALL_H

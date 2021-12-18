//
// Created by unrelated on 2021/11/22.
//

#ifndef VM_CALL_H
#define VM_CALL_H

#include "../PCode.h"

class CALL : public PCode {
public:
    const Type type;
//    const std::string name;
    const std::string funcName;
    std::vector<std::string> formalParams;
public:
    CALL(std::string funcName) : type(Type::CALL), funcName(funcName) {}

    CALL(std::string funcName, std::vector<std::string> formalParams)
            : type(Type::CALL),
              funcName(funcName),
              formalParams(formalParams) {}

    virtual std::string to_string() const override {
        return std::string{"CALL "} + funcName;
    }
};


#endif //VM_CALL_H

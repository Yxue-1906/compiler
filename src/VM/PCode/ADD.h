//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_ADD_H
#define VM_ADD_H

#include "../PCode.h"

namespace INTERPRETER {
    class ADD : public PCode {
    public:
        const Type type;
        const std::string name1;
        const std::string name2;
        const std::string toStore;

    public:
        ADD(std::string name1, std::string name2, std::string toStore)
                : type(Type::ADD), name1(name1), name2(name2), toStore(toStore) {}

        virtual std::string to_string() const override {
            return std::string{"ADD "} + name1 + '+' + name2 + "->" + toStore;
        }
    };
}


#endif //VM_ADD_H

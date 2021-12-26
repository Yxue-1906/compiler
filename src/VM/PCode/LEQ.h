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

        virtual std::string to_string() const override {
            return std::string{"LEQ "} + left + ' ' + right + ' ' + toStore;
        }
    };
}


#endif //VM_LEQ_H

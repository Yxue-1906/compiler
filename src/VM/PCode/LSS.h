//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_LSS_H
#define VM_LSS_H

#include "../PCode.h"

namespace INTERPRETER {
    class LSS : public PCode {
    public:
        const Type type;
        const std::string left;
        const std::string right;
        const std::string toStore;

    public:
        LSS(std::string left, std::string right, std::string toStore)
                : type(Type::LSS), left(left), right(right), toStore(toStore) {}

        virtual std::string to_string() const override {
            return std::string{"LSS "} + left + ' ' + right + ' ' + toStore;
        }
    };
}


#endif //VM_LSS_H

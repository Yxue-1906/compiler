//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_EQ_H
#define VM_EQ_H

#include "../PCode.h"

namespace INTERPRETER {
    class EQ : public PCode {
    public:
        const Type type;
        const std::string left;
        const std::string right;
        const std::string toStore;

    public:
        EQ(std::string left, std::string right, std::string toStore)
                : type(Type::EQ), left(left), right(right), toStore(toStore) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return std::string{"EQ "} + left + ' ' + right + ' ' + toStore;//todo
        }
    };
}


#endif //VM_EQ_H

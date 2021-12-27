//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_GEQ_H
#define VM_GEQ_H

#include <memory>
#include "../PCode.h"

namespace INTERPRETER {
    class GEQ : public PCode {
    public:
        const Type type;
        const std::string left;
        const std::string right;
        const std::string toStore;

    public:
        GEQ(std::string left, std::string right, std::string toStore)
                : type(Type::GEQ), left(left), right(right), toStore(toStore) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return std::string{"GEQ "} + left + ' ' + right + ' ' + toStore;
        }
    };
}


#endif //VM_GEQ_H

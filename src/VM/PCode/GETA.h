//
// Created by unrelated on 2021/11/24.
//

#ifndef VM_GETA_H
#define VM_GETA_H

#include "../PCode.h"

namespace INTERPRETER {
    class GETA : public PCode {
    public:
        const Type type;
        const std::string toStore;
        const std::string from;

    public:
        GETA(std::string toStore, std::string from)
                : type(Type::GETA), toStore(toStore), from(from) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            return std::string{"GETA &"} + from + "->" + toStore;
        }
    };
}


#endif //VM_GETA_H

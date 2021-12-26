//
// Created by unrelated on 2021/12/26.
//

#ifndef SRC_PARSER_NOT_H
#define SRC_PARSER_NOT_H

#include "../PCode.h"

namespace INTERPRETER {
    class NOT : public PCode {
    public:
        const Type type;
        const std::string toStore;
        const std::string right;

    public:
        NOT(std::string right, std::string toStore)
                : type(Type::NOT), right(right), toStore(toStore) {}

        virtual std::string to_string() const override {
            return std::string{"NOT "} + right + "->" + toStore;
        }
    };
}


#endif //SRC_PARSER_NOT_H

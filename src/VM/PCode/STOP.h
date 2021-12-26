//
// Created by unrelated on 2021/12/22.
//

#ifndef SRC_PARSER_STOP_H
#define SRC_PARSER_STOP_H

#include "../PCode.h"

namespace INTERPRETER {
    class STOP : public PCode {
    public:
        const Type type;
        const std::string value;
        const std::string base;
        const int offset;

    public:
        STOP(std::string value, std::string base, int offset)
                : type(Type::STOP), value(value), base(base), offset(offset) {}

        virtual std::string to_string() const override {
            return std::string{"STOP "} + value + " " + base + " " + std::to_string(offset);
        }
    };
}


#endif //SRC_PARSER_STOP_H

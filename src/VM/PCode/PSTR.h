//
// Created by unrelated on 2021/12/29.
//

#ifndef SRC_PARSER_PSTR_H
#define SRC_PARSER_PSTR_H

#include <memory>
#include "../PCode.h"

namespace INTERPRETER {
    class PSTR : public PCode {
    public:
        Type type;
        const std::string str;

    public:
        PSTR(std::string str) : type(Type::PSTR), str(str) {}

        virtual std::string
        to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const override {
            std::string toRetrun = "PSTR ";
            toRetrun += str;
            return toRetrun;
        }
    };
}


#endif //SRC_PARSER_PSTR_H

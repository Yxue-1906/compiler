//
// Created by unrelated on 2021/11/21.
//

#ifndef VM_PINT_H
#define VM_PINT_H

#include "../PCode.h"

class PINT : public PCode {
public:
    Type type;

public:
    PINT() : type(Type::PINT) {}

    virtual std::string to_string() const {
        return std::string{"PINT"};
    }
};


#endif //VM_PINT_H

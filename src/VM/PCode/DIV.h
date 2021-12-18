//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_DIV_H
#define VM_DIV_H

#include "../PCode.h"

/**
 * 将栈顶除以次栈顶并弹出, 将结果入栈
 */
class DIV : public PCode {
public:
    const Type type;
    const std::string name1;
    const std::string name2;
    const std::string toStore;

public:
    DIV(std::string name1, std::string name2, std::string toStore)
            : type(Type::DIV), name1(name1), name2(name2), toStore(toStore) {}

    virtual std::string to_string() const override {
        return std::string{"DIV "} + name1 + ' ' + name2 + ' ' + toStore;
    }
};


#endif //VM_DIV_H

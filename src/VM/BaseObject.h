//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_BASEOBJECT_H
#define VM_BASEOBJECT_H

#include <string>

class BaseObject {
public:
    virtual std::string to_string() const = 0;
};


#endif //VM_BASEOBJECT_H

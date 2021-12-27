//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_BASEOBJECT_H
#define VM_BASEOBJECT_H

#include <string>
#include <vector>
#include <memory>

class BaseObject {
public:
    virtual std::string to_string() const { return ""; }
};


#endif //VM_BASEOBJECT_H

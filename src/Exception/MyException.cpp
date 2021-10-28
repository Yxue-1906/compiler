//
// Created by unrelated on 2021/10/28.
//

#include "MyException.h"

std::string MyException::getBaseInfo() {
    std::string toReturn = std::to_string(lineNumber) + ' ' + type;
    return toReturn;
}
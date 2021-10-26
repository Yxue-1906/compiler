//
// Created by unrelated on 2021/9/28.
//

#include "MyException.h"

std::ostream *MyException::os_p = nullptr;
bool MyException::debug = false;

MyException::MyException(int line_number, char type)
        : std::exception(), line_number(line_number), type(type) {}

MyException::~MyException() = default;

void MyException::initOutput(std::ostream *os_p) {
    if (!MyException::os_p) {
        if (dynamic_cast<const std::ofstream *>(os_p)) {
            if (!os_p->good())
                std::cerr << "error! os_p is not good, on" << __FILE__ << ":" << __LINE__ << std::endl;
            throw MyException(-1, 'g');
        }
        MyException::os_p = os_p;
    }
}

bool MyException::setDebug(bool debug) {
    MyException::debug = debug;
    return debug;
}

const char *MyException::what() const noexcept {
    if (!os_p) {
        std::cerr << "os_p isn't init!" << std::endl;
        return nullptr;
    }
    (*os_p) << line_number << ' ' << type;
    if (debug)(*os_p) << message;
    (*os_p) << std::endl;
}
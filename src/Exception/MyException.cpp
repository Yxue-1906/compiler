//
// Created by unrelated on 2021/9/28.
//

#include <memory>
#include "MyException.h"

std::ostream *MyException::os_p = nullptr;
bool MyException::debug = false;

MyException::MyException(int line_number, char type) noexcept
        : std::exception(), line_number(line_number), type(type) {}

MyException::MyException(int line_number, char type, std::string message) noexcept
        : std::exception(), line_number(line_number), type(type) {
    this->message.append(message);
}

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

MyException *MyException::addMessage(char *message) {
    this->message.append(message);
    this->message.push_back('\n');
    return this;

}

MyException *MyException::addMessage(std::string *message) {
    this->message.append(*message);
    this->message.push_back('\n');
    return this;
}

std::string MyException::getMessage() {
    return this->message;
}
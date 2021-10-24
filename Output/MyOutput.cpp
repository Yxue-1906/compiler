//
// Created by unrelated on 2021/10/17.
//

#include "MyOutput.h"

std::ostream *MyOutput::os = nullptr;

void MyOutput::setOutput(std::string &file) {
    if (os) {
        if (dynamic_cast<std::ofstream *>(os) &&
            !dynamic_cast<std::ofstream *>(os)->is_open())
            dynamic_cast<std::ofstream *>(os)->open(file, std::ios::out);
    } else {
        auto *ofs_p = new std::ofstream(file, std::ios::out);
        os = ofs_p;
    }
}

void MyOutput::setOutput(std::ostream *os) {
    if (MyOutput::os) {
        if (dynamic_cast<std::ofstream *>(MyOutput::os) &&
            !dynamic_cast<std::ofstream *>(MyOutput::os)->is_open())
            MyOutput::os = os;
    } else {
        MyOutput::os = os;
    }
}

std::ostream *MyOutput::getOs() {
    if (!os->good()) {
        throw MyException();
    }
    if (os) {
        if (dynamic_cast<std::ofstream *>(os)) {
            if (dynamic_cast<std::ofstream *>(os)->is_open())return os;
        }
        return os;
    }
    std::cout << "error, os isn't initialized" << std::endl;
    throw MyException();
}

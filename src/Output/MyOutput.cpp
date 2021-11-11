//
// Created by unrelated on 2021/10/17.
//

#include "MyOutput.h"
#include "../Exception/MyException.h"

std::ostream *MyOutput::os = nullptr;
std::ostream *MyOutput::eos = nullptr;

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

void MyOutput::setErrorOutput(std::string &file) {
    if (eos) {
        if (dynamic_cast<std::ofstream *>(eos) &&
            !dynamic_cast<std::ofstream *>(eos)->is_open())
            dynamic_cast<std::ofstream *>(eos)->open(file, std::ios::out);
    } else {
        auto *ofs_p = new std::ofstream(file, std::ios::out);
        eos = ofs_p;
    }
}

void MyOutput::setErrorOutput(std::ostream *eos) {
    if (MyOutput::eos) {
        if (dynamic_cast<std::ofstream *>(MyOutput::eos) &&
            !dynamic_cast<std::ofstream *>(MyOutput::eos)->is_open())
            MyOutput::eos = eos;
    } else {
        MyOutput::eos = eos;
    }
}

std::ostream *MyOutput::getOs() {
    if (!os->good()) {
        throw MyException(-1, 'g');
    }
    if (os) {
        if (dynamic_cast<std::ofstream *>(os)) {
            if (dynamic_cast<std::ofstream *>(os)->is_open())return os;
        }
        return os;
    }
    std::cout << "error, os isn't initialized" << std::endl;
    throw MyException(-1, 'g');
}

std::ostream *MyOutput::getEos() {
    if (!eos->good()) {
        throw MyException(-1, 'g');
    }
    if (eos) {
        if (dynamic_cast<std::ofstream *>(eos)) {
            if (dynamic_cast<std::ofstream *>(eos)->is_open())return eos;
        }
        return eos;
    }
    std::cout << "error, os isn't initialized" << std::endl;
    throw MyException(-1, 'g');
}

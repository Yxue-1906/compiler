//
// Created by unrelated on 2021/10/17.
//

#include "MyOutput.h"

std::ofstream MyOutput::ofs;

void MyOutput::setOutput(std::string file) {
    if (!ofs.is_open())
        ofs.open(file, std::ios::out);
}

void MyOutput::setOutput(std::ofstream &ofs) {
    std::cout << ofs.is_open() << std::endl;
    if (!MyOutput::ofs.is_open())
        MyOutput::ofs = std::move(ofs);
}

std::ofstream &MyOutput::getOfs() {
    if (ofs.is_open())
        return ofs;
    else {
        std::cout << "ofs is not initialized!" << std::endl;
        throw new MyException();
    }

}

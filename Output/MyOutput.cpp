//
// Created by unrelated on 2021/10/17.
//

#include "MyOutput.h"

void MyOutput::setOutput(std::string file) {
    if (!ofs.is_open())
        ofs.open(file, std::ios::out);
}

std::ofstream &MyOutput::getOfs() {
    if (ofs.is_open())
        return ofs;
    else
        std::cout << "ofs is not initialized!" << std::endl;
}

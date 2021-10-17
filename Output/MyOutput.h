//
// Created by unrelated on 2021/10/17.
//

#ifndef MYOUTPUT_H
#define MYOUTPUT_H

#include "iostream"
#include "fstream"
#include "../Exception/MyException.h"

class MyOutput {
public:
private:
    static std::ofstream ofs;
public:
    static void setOutput(std::string);

    virtual void myOutput() = 0;

protected:
    std::ofstream &getOfs();

};


#endif //MYOUTPUT_H

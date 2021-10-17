//
// Created by unrelated on 2021/10/17.
//

#ifndef MYOUTPUT_H
#define MYOUTPUT_H

#include "iostream"
#include "fstream"

class MyOutput {
public:
private:
    static std::ofstream ofs;
public:
    static void setOutput(std::string);

protected:
    std::ofstream &getOfs();

    virtual void myOutput() = 0;
};


#endif //MYOUTPUT_H

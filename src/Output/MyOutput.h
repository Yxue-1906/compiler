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
    static std::ostream *os;
public:
    MyOutput() = default;

    ~MyOutput() = default;

    static void setOutput(std::string &);

    static void setOutput(std::ostream *);

    virtual void myOutput() = 0;


protected:
    std::ostream *getOs();

};


#endif //MYOUTPUT_H

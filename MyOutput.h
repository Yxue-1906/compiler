//
// Created by unrelated on 2021/10/8.
//

#ifndef PARSER_MYOUTPUT_H
#define PARSER_MYOUTPUT_H

#include <iostream>
#include <fstream>

class MyOutput {
public:

private:
    static std::ofstream out{"output.txt"};
public:

    MyOutput(bool);

    template<class F>
    MyOutput operator<<(F f) {
        if (enable)std::cout << f;
        return *this;
    }

    bool setEnable(bool);

public:
    bool enable = false;
};


#endif //PARSER_MYOUTPUT_H

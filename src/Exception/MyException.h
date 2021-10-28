//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_MYEXCEPTION_H
#define SRC_PARSER_MYEXCEPTION_H


#include <exception>
#include <string>

class MyException : public std::exception {
private:
    const int lineNumber;
    const char type;

public:
    MyException(int lineNumber, char type) : lineNumber(lineNumber), type(type) {}

    std::string getBaseInfo();

    virtual std::string getInfo() = 0;
};


#endif //SRC_PARSER_MYEXCEPTION_H

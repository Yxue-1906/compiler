//
// Created by unrelated on 2021/9/28.
//

#ifndef LEXER_MYEXCEPTION_H
#define LEXER_MYEXCEPTION_H


#include <exception>

class MyException : std::exception {
public:
    //public attributes
    //const int id;

private:
    //private attributes
    //static unsigned long long int now_id = 0;

public:
    //public methods
    MyException();

    ~MyException() override;

private:
    //private methods

};


#endif //LEXER_MYEXCEPTION_H

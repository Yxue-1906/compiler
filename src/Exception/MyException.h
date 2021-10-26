//
// Created by unrelated on 2021/9/28.
//

#ifndef LEXER_MYEXCEPTION_H
#define LEXER_MYEXCEPTION_H


#include <exception>
#include "../Output/MyOutput.h"

class MyException : public std::exception {
public:
    //public attributes
    //const int id;

private:
    //private attributes
    static std::ostream *os_p;
    static bool debug;

    const int line_number;
    const char type;

    std::string message;

public:
    //public methods
    MyException(int line_number, char type);

    ~MyException() override;

    static void initOutput(std::ostream *os_p);

    static bool setDebug(bool debug);

    virtual const char *what() const noexcept override;

    MyException *addMessage(char *) {
        this->message.append(message);
        this->message.push_back('\n');
        return this;
    }

    MyException *addMessage(std::string *) {
        this->message.append(*message);
        this->message.push_back('\n');
        return this;
    }

private:
    //private methods

};


#endif //LEXER_MYEXCEPTION_H

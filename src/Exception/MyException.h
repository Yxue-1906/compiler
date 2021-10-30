//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_MYEXCEPTION_H
#define SRC_PARSER_MYEXCEPTION_H


#include <exception>
#include <string>
#include "../Lexer/TokenBase.h"

class MyException : public std::exception, public MyOutput {
private:
    const int lineNumber;
    const char type;

protected:
    std::string message;

public:
    MyException(const TokenBase &token, char type)
            : std::exception(), MyOutput(), lineNumber(token.getLineNumber()), type(type) {}

    MyException(int lineNumber, char type) : std::exception(), MyOutput(), lineNumber(lineNumber), type(type) {}

    virtual void myOutput() override {
        auto os = getOs();
        (*os) << lineNumber << ' ' << type;
#ifdef DEBUG
        (*os) << ':' << message;
#endif // DEBUG
        (*os) << std::endl;
    }

    virtual void addMessage(std::string message) {
        this->message.append(message);
    }

};


#endif //SRC_PARSER_MYEXCEPTION_H

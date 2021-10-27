//
// Created by unrelated on 2021/10/25.
//

#ifndef PARSER_ILLEGALCHAREXCEPTION_H
#define PARSER_ILLEGALCHAREXCEPTION_H

#include "MyException.h"

class IllegalCharException : public MyException {
private:

public:
private:
public:
    IllegalCharException(int line_number, std::string ilstr) : MyException(line_number, 'a') {
        message.append(ilstr);
    }

};


#endif //PARSER_ILLEGALCHAREXCEPTION_H

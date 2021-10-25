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
    IllegalCharException(STRCON *token) {
        this->token = token;
    }

};


#endif //PARSER_ILLEGALCHAREXCEPTION_H

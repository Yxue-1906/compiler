//
// Created by unrelated on 2021/10/25.
//

#ifndef PARSER_ILLEGALCHAREXCEPTION_H
#define PARSER_ILLEGALCHAREXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class IllegalCharException : public MyException {
public:
    IllegalCharException(const TokenBase &token) : MyException(token, 'a') {}

    IllegalCharException(int line_number) : MyException(line_number, 'a') {}

    IllegalCharException(const TokenBase &token, std::string message) : MyException(token, 'a') {
        this->message.append(message);
    }

    IllegalCharException(int line_number, std::string message) : MyException(line_number, 'a') {
        this->message.append(message);
    }

};


#endif //PARSER_ILLEGALCHAREXCEPTION_H

//
// Created by unrelated on 2021/11/4.
//

#ifndef SRC_PARSER_MISMATCHCALLTYPEEXCEPTION_H
#define SRC_PARSER_MISMATCHCALLTYPEEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchCallTypeException : public MyException {
public:
    explicit MismatchCallTypeException(const TokenBase &token) : MyException(token, 'e') {}

    explicit MismatchCallTypeException(int lineNumber) : MyException(lineNumber, 'e') {}

    MismatchCallTypeException(const TokenBase &token, const std::string &message) : MyException(token, 'e') {
        this->message.append(message);
    }

    MismatchCallTypeException(int lineNumber, const std::string &message) : MyException(lineNumber, 'e') {
        this->message.append(message);
    }

};


#endif //SRC_PARSER_MISMATCHCALLTYPEEXCEPTION_H

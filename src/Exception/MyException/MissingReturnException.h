//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MISSINGRETURNEXCEPTION_H
#define SRC_PARSER_MISSINGRETURNEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MissingReturnException : public MyException {
public:
    explicit MissingReturnException(const TokenBase &token) : MyException(token, 'g') {}

    explicit MissingReturnException(int lineNumber) : MyException(lineNumber, 'g') {}

    MissingReturnException(const TokenBase &token, const std::string &message) : MyException(token, 'g') {
        this->message.append(message);
    }

    MissingReturnException(int lineNumber, const std::string &message) : MyException(lineNumber, 'g') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_MISSINGRETURNEXCEPTION_H

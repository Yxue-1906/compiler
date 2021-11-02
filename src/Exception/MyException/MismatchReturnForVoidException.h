//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MISMATCHRETURNFORVOIDEXCEPTION_H
#define SRC_PARSER_MISMATCHRETURNFORVOIDEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchReturnForVoidException : public MyException {
public:
    explicit MismatchReturnForVoidException(const TokenBase &token) : MyException(token, 'f') {}

    explicit MismatchReturnForVoidException(int lineNumber) : MyException(lineNumber, 'f') {}

    MismatchReturnForVoidException(const TokenBase &token, const std::string &message) : MyException(token, 'f') {
        this->message.append(message);
    }

    MismatchReturnForVoidException(int lineNumber, const std::string &message) : MyException(lineNumber, 'f') {
        this->message.append(message);
    }
};

#endif //SRC_PARSER_MISMATCHRETURNFORVOIDEXCEPTION_H

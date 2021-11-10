//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MISMATCHRETURNFORNONVOIDEXCEPTION_H
#define SRC_PARSER_MISMATCHRETURNFORNONVOIDEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchReturnForNonVoidException : public MyException {
public:
    explicit MismatchReturnForNonVoidException(const TokenBase &token) : MyException(token, 'g') {}

    explicit MismatchReturnForNonVoidException(int lineNumber) : MyException(lineNumber, 'g') {}

    MismatchReturnForNonVoidException(const TokenBase &token, const std::string &message) : MyException(token, 'g') {
        this->message.append(message);
    }

    MismatchReturnForNonVoidException(int lineNumber, const std::string &message) : MyException(lineNumber, 'g') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_MISMATCHRETURNFORNONVOIDEXCEPTION_H

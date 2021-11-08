//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MISMATCHRETURNFORNONVOIDEXCEPTION_H
#define SRC_PARSER_MISMATCHRETURNFORNONVOIDEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchReturnForNonVoidException : public MyException {
public:
    explicit MismatchReturnForNonVoidException(const TokenBase &token) : MyException(token, 'b') {}

    explicit MismatchReturnForNonVoidException(int lineNumber) : MyException(lineNumber, 'b') {}

    MismatchReturnForNonVoidException(const TokenBase &token, const std::string &message) : MyException(token, 'b') {
        this->message.append(message);
    }

    MismatchReturnForNonVoidException(int lineNumber, const std::string &message) : MyException(lineNumber, 'b') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_MISMATCHRETURNFORNONVOIDEXCEPTION_H

//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_MISMATCHPARAMNUMEXCEPTION_H
#define SRC_PARSER_MISMATCHPARAMNUMEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchParamNumException : public MyException {
public:
    explicit MismatchParamNumException(const TokenBase &token) : MyException(token, 'd') {}

    explicit MismatchParamNumException(int lineNumber) : MyException(lineNumber, 'd') {}

    MismatchParamNumException(const TokenBase &token, const std::string &message) : MyException(token, 'd') {
        this->message.append(message);
    }

    MismatchParamNumException(int lineNumber, const std::string &message) : MyException(lineNumber, 'd') {
        this->message.append(message);
    }

};


#endif //SRC_PARSER_MISMATCHPARAMNUMEXCEPTION_H

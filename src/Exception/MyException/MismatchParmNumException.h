//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_MISMATCHPARMNUMEXCEPTION_H
#define SRC_PARSER_MISMATCHPARMNUMEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchParmNumException : public MyException {
public:
    explicit MismatchParmNumException(const TokenBase &token) : MyException(token, 'd') {}

    explicit MismatchParmNumException(int lineNumber) : MyException(lineNumber, 'd') {}

    MismatchParmNumException(const TokenBase &token, const std::string& message) : MyException(token, 'd') {
        this->message.append(message);
    }

    MismatchParmNumException(int lineNumber, const std::string& message) : MyException(lineNumber, 'd') {
        this->message.append(message);
    }

};


#endif //SRC_PARSER_MISMATCHPARMNUMEXCEPTION_H

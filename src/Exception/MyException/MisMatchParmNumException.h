//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_MISMATCHPARMNUMEXCEPTION_H
#define SRC_PARSER_MISMATCHPARMNUMEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MisMatchParmNumException : public MyException {
public:
    MisMatchParmNumException(const TokenBase &token) : MyException(token, 'd') {}

    MisMatchParmNumException(int lineNumber) : MyException(lineNumber, 'd') {}

    MisMatchParmNumException(const TokenBase &token, std::string message) : MyException(token, 'd') {
        this->message.append(message);
    }

    MisMatchParmNumException(int lineNumber, std::string message) : MyException(lineNumber, 'd') {
        this->message.append(message);
    }

};


#endif //SRC_PARSER_MISMATCHPARMNUMEXCEPTION_H

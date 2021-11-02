//
// Created by unrelated on 2021/10/26.
//

#ifndef PARSER_DUPIDENTEXCEPTION_H
#define PARSER_DUPIDENTEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class DupIdentException : public MyException {
public:
    explicit DupIdentException(const TokenBase &token) : MyException(token, 'b') {}

    explicit DupIdentException(int lineNumber) : MyException(lineNumber, 'b') {}

    DupIdentException(const TokenBase &token, const std::string &message) : MyException(token, 'b') {
        this->message.append(message);
    }

    DupIdentException(int lineNumber, const std::string &message) : MyException(lineNumber, 'b') {
        this->message.append(message);
    }
};

#endif //PARSER_DUPIDENTEXCEPTION_H

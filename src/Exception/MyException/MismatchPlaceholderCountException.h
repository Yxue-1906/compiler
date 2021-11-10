//
// Created by unrelated on 2021/11/2.
//

#ifndef SRC_PARSER_MISMATCHPLACEHOLDERCOUNTEXCEPTION_H
#define SRC_PARSER_MISMATCHPLACEHOLDERCOUNTEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MismatchPlaceholderCountException : public MyException {
public:
    explicit MismatchPlaceholderCountException(const TokenBase &token) : MyException(token, 'l') {}

    explicit MismatchPlaceholderCountException(int lineNumber) : MyException(lineNumber, 'l') {}

    MismatchPlaceholderCountException(const TokenBase &token, const std::string &message) : MyException(token, 'l') {
        this->message.append(message);
    }

    MismatchPlaceholderCountException(int lineNumber, const std::string &message) : MyException(lineNumber, 'l') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_MISMATCHPLACEHOLDERCOUNTEXCEPTION_H

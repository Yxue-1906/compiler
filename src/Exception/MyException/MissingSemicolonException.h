//
// Created by unrelated on 2021/10/30.
//

#ifndef SRC_PARSER_MISSINGSEMICOLONEXCEPTION_H
#define SRC_PARSER_MISSINGSEMICOLONEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MissingSemicolonException : public MyException {
public:
    MissingSemicolonException(const TokenBase &token) : MyException(token, 'i') {}

    MissingSemicolonException(int lineNumber) : MyException(lineNumber, 'i') {}

    MissingSemicolonException(const TokenBase &token, const std::string &message) : MyException(token, 'i') {
        this->message.append(message);
    }

    MissingSemicolonException(int lineNumber, const std::string &message) : MyException(lineNumber, 'i') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_MISSINGSEMICOLONEXCEPTION_H

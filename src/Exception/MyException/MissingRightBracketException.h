//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MISSINGRIGHTBRACKETEXCEPTION_H
#define SRC_PARSER_MISSINGRIGHTBRACKETEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MissingRightBracketException : public MyException {
public:
    explicit MissingRightBracketException(const TokenBase &token) : MyException(token, 'k') {}

    explicit MissingRightBracketException(int lineNumber) : MyException(lineNumber, 'k') {}

    MissingRightBracketException(const TokenBase &token, const std::string &message) : MyException(token, 'k') {
        this->message.append(message);
    }

    MissingRightBracketException(int lineNumber, const std::string &message) : MyException(lineNumber, 'k') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_MISSINGRIGHTBRACKETEXCEPTION_H

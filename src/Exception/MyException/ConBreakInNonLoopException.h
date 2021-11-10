//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_CONBREAKINNONLOOPEXCEPTION_H
#define SRC_PARSER_CONBREAKINNONLOOPEXCEPTION_H

#include "../MyException.h"

class ConBreakInNonLoopException : public MyException {
public:
    explicit ConBreakInNonLoopException(const TokenBase &token) : MyException(token, 'm') {}

    explicit ConBreakInNonLoopException(int lineNumber) : MyException(lineNumber, 'm') {}

    ConBreakInNonLoopException(const TokenBase &token, const std::string &message) : MyException(token, 'm') {
        this->message.append(message);
    }

    ConBreakInNonLoopException(int lineNumber, const std::string &message) : MyException(lineNumber, 'm') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_CONBREAKINNONLOOPEXCEPTION_H

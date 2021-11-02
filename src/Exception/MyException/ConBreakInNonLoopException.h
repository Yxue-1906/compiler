//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_CONBREAKINNONLOOPEXCEPTION_H
#define SRC_PARSER_CONBREAKINNONLOOPEXCEPTION_H


class ConBreakInNonLoopException: public MyException{
public:
    explicit ConBreakInNonLoopException(const TokenBase &token) : MyException(token, 'k') {}

    explicit ConBreakInNonLoopException(int lineNumber) : MyException(lineNumber, 'k') {}

    ConBreakInNonLoopException(const TokenBase &token, const std::string &message) : MyException(token, 'k') {
        this->message.append(message);
    }

    ConBreakInNonLoopException(int lineNumber, const std::string &message) : MyException(lineNumber, 'k') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_CONBREAKINNONLOOPEXCEPTION_H

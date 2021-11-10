//
// Created by unrelated on 2021/11/10.
//

#ifndef SRC_PARSER_ASSIGNTOCONSTEXCEPTION_H
#define SRC_PARSER_ASSIGNTOCONSTEXCEPTION_H

#include "../MyException.h"

class AssignToConstException : public MyException {
public:
    explicit AssignToConstException(const TokenBase &token) : MyException(token, 'h') {}

    explicit AssignToConstException(int lineNumber) : MyException(lineNumber, 'h') {}

    AssignToConstException(const TokenBase &token, const std::string &message) : MyException(token, 'h') {
        this->message.append(message);
    }

    AssignToConstException(int lineNumber, const std::string &message) : MyException(lineNumber, 'h') {
        this->message.append(message);
    }
};


#endif //SRC_PARSER_ASSIGNTOCONSTEXCEPTION_H

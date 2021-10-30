//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_UNDEFIDENTEXCEPTION_H
#define SRC_PARSER_UNDEFIDENTEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class UndefIdentException : public MyException {
public:
    UndefIdentException(int line_number, std::string undefIdentName) : MyException(line_number, 'c') {
        this->message.append(undefIdentName);
    }

    UndefIdentException(const TokenBase &token, std::string undefIdentName) : MyException(token, 'c') {
        this->message.append(undefIdentName);
    }

    UndefIdentException(int line_number) : MyException(line_number, 'c') {}

    UndefIdentException(const TokenBase &token) : MyException(token, 'c') {}
};


#endif //SRC_PARSER_UNDEFIDENTEXCEPTION_H

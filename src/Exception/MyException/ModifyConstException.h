//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MODIFYCONSTEXCEPTION_H
#define SRC_PARSER_MODIFYCONSTEXCEPTION_H


#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class ModifyConstException : public MyException {
public:
    ModifyConstException(int line_number, std::string message) : MyException(line_number, 'h') {
        this->message.append(message);
    }

    ModifyConstException(const TokenBase &token, std::string message) : MyException(token, 'h') {
        this->message.append(message);
    }

    ModifyConstException(int line_number) : MyException(line_number, 'h') {}

    ModifyConstException(const TokenBase &token) : MyException(token, 'h') {}
};


#endif //SRC_PARSER_MODIFYCONSTEXCEPTION_H

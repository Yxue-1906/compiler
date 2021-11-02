//
// Created by unrelated on 2021/10/31.
//

#ifndef SRC_PARSER_MISSINGRIGHTPARENTHESISEXCEPTION_H
#define SRC_PARSER_MISSINGRIGHTPARENTHESISEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class MissingRightParenthesisException : public MyException {
public:
    explicit MissingRightParenthesisException(const TokenBase &token) : MyException(token, 'j') {}

    explicit MissingRightParenthesisException(int line_number) : MyException(line_number, 'j') {}

    MissingRightParenthesisException(const TokenBase &token, std::string message) : MyException(token, 'j') {
        this->message.append(message);
    }

    MissingRightParenthesisException(int line_number, std::string message) : MyException(line_number, 'j') {
        this->message.append(message);
    }

};


#endif //SRC_PARSER_MISSINGRIGHTPARENTHESISEXCEPTION_H

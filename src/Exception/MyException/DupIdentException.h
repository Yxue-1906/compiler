//
// Created by unrelated on 2021/10/26.
//

#ifndef PARSER_DUPIDENTEXCEPTION_H
#define PARSER_DUPIDENTEXCEPTION_H

#include "../MyException.h"
#include "../../Lexer/TokenBase.h"

class DupIdentException : public MyException {
public:
    DupIdentException(const TokenBase &token) : MyException(token, 'b') {}

    DupIdentException(int line_number) : MyException(line_number, 'b') {}

};


#endif //PARSER_DUPIDENTEXCEPTION_H

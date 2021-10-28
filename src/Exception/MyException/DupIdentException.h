//
// Created by unrelated on 2021/10/26.
//

#ifndef PARSER_DUPIDENTEXCEPTION_H
#define PARSER_DUPIDENTEXCEPTION_H

#include "../MyException.h"

class DupIdentException : public MyException {
private:
public:
private:
public:
    DupIdentException(int line_number) : MyException(line_number, 'b') {}

};


#endif //PARSER_DUPIDENTEXCEPTION_H

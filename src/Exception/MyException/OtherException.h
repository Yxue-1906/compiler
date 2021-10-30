//
// Created by unrelated on 2021/10/30.
//

#ifndef SRC_PARSER_OTHEREXCEPTION_H
#define SRC_PARSER_OTHEREXCEPTION_H

#include "../MyException.h"

class OtherException : public MyException {
private:

public:
    OtherException() : MyException(-1, 'g') {}

    OtherException(std::string message) : MyException(-1, 'g') {
        this->message.append(message);
    }


};


#endif //SRC_PARSER_OTHEREXCEPTION_H

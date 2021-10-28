//
// Created by unrelated on 2021/10/28.
//

#ifndef SRC_PARSER_UNDEFIDENTEXCEPTION_H
#define SRC_PARSER_UNDEFIDENTEXCEPTION_H


class UndefIdentException : public MyException {
public:
    UndefIdentException(int line_number, std::string undefIdentName);
};


#endif //SRC_PARSER_UNDEFIDENTEXCEPTION_H

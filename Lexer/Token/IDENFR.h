//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_IDENFR_H
#define PARSER_IDENFR_H

#include "Token.h"

class IDENFR : public Token {
private:
    const std::string value;
public:
    IDENFR(std::string value) : Token(1), value(value) {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << ident << std::endl;
    }
};


#endif //PARSER_IDENFR_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_IDENFR_H
#define PARSER_IDENFR_H

#include <utility>

#include "../Token.h"

class IDENFR : public Token {
private:
public:
    IDENFR(std::string value) : Token(Token::IDENFR) {
        setValue_p(new std::string(std::move(value)));
    }

public:
};


#endif //PARSER_IDENFR_H

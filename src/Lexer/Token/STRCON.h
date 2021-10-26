#include <utility>

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_STRCON_H
#define PARSER_STRCON_H


class STRCON : public Token {
private:
    const int count = 0;
public:
    STRCON(std::string value, int count) : Token(Token::STRCON), count(count) {
        setValue_p(new std::string(std::move(value)));
    }

public:
};


#endif //PARSER_STRCON_H

#include <utility>

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_STRCON_H
#define PARSER_STRCON_H


class STRCON : public Token<std::string> {
public:
    STRCON(const std::string &value)
            : Token(TokenBase::STRCON, std::make_shared<std::string>(value)) {}

public:
};


#endif //PARSER_STRCON_H

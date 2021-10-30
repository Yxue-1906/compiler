//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_IDENFR_H
#define PARSER_IDENFR_H

#include <utility>

#include "../TokenBase.h"

class IDENFR : public Token<std::string> {
private:
public:
    IDENFR(const std::string &value) : Token(TokenBase::IDENFR,
                                             std::make_shared<std::string>(value)) {}

public:
};


#endif //PARSER_IDENFR_H

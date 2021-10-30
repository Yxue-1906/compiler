//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MULT_H
#define PARSER_MULT_H

class MULT : public Token<std::string> {
private:
public:
    MULT() : Token(TokenBase::MULT,
                   std::make_shared<std::string>("*")) {}

public:
};

#endif //PARSER_MULT_H

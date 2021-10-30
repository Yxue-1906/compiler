//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MINU_H
#define PARSER_MINU_H

class MINU : public Token<std::string> {
private:
public:
    MINU() : Token(TokenBase::MINU,
                   std::make_shared<std::string>("-")) {}

public:
};

#endif //PARSER_MINU_H

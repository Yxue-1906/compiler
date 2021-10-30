//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_IFTK_H
#define PARSER_IFTK_H


class IFTK : public Token<std::string> {
private:
public:
    IFTK() : Token(TokenBase::IFTK,
                   std::make_shared<std::string>("if")) {}

public:
};


#endif //PARSER_IFTK_H

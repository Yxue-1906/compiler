//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MAINTK_H
#define PARSER_MAINTK_H


class MAINTK : public Token<std::string> {
private:
public:
    MAINTK() : Token(TokenBase::MAINTK,
                     std::make_shared<std::string>("main")) {}

public:
};


#endif //PARSER_MAINTK_H

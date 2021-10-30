//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_BREAKTK_H
#define PARSER_BREAKTK_H


class BREAKTK : public Token<std::string> {
private:
public:
    BREAKTK() : Token(TokenBase::BREAKTK,
                      std::make_shared<std::string>("break")) {}

public:
};


#endif //PARSER_BREAKTK_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_PRINTFTK_H
#define PARSER_PRINTFTK_H


class PRINTFTK : public Token<std::string> {
private:
public:
    PRINTFTK() : Token(TokenBase::PRINTFTK,
                       std::make_shared<std::string>("printf")) {}

public:
};


#endif //PARSER_PRINTFTK_H

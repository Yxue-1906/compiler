//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_VOIDTK_H
#define PARSER_VOIDTK_H


class VOIDTK : public Token<std::string> {
private:
public:
    VOIDTK() : Token(TokenBase::VOIDTK,
                     std::make_shared<std::string>("void")) {}

public:
    \

};

#endif //PARSER_VOIDTK_H

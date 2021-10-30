//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RETURNTK_H
#define PARSER_RETURNTK_H


class RETURNTK : public Token<std::string> {
private:
public:
    RETURNTK() : Token(TokenBase::RETURNTK,
                       std::make_shared<std::string>("return")) {}

public:
};

#endif //PARSER_RETURNTK_H

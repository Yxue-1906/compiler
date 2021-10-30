//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_ASSIGN_H
#define PARSER_ASSIGN_H


class ASSIGN : public Token<std::string> {
private:
public:
    ASSIGN() : Token(TokenBase::ASSIGN,
                     std::make_shared<std::string>("=")) {}

public:
};

#endif //PARSER_ASSIGN_H

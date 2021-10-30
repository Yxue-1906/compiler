//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RBRACE_H
#define PARSER_RBRACE_H


class RBRACE : public Token<std::string> {
private:
public:
    RBRACE() : Token(TokenBase::RBRACE,
                     std::make_shared<std::string>("}")) {}

public:
};

#endif //PARSER_RBRACE_H

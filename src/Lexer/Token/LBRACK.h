//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LBRACK_H
#define PARSER_LBRACK_H


class LBRACK : public Token<std::string> {
private:
public:
    LBRACK() : Token(TokenBase::LBRACK,
                     std::make_shared<std::string>("[")) {}

public:
};

#endif //PARSER_LBRACK_H

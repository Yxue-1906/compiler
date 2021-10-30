//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_EQL_H
#define PARSER_EQL_H


class EQL : public Token<std::string> {
private:
public:
    EQL() : Token(TokenBase::EQL,
                  std::make_shared<std::string>("==")) {}

public:
};

#endif //PARSER_EQL_H

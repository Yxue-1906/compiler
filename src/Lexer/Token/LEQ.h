//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LEQ_H
#define PARSER_LEQ_H


class LEQ : public Token<std::string> {
private:
public:
    LEQ() : Token(TokenBase::LEQ,
                  std::make_shared<std::string>("<=")) {}

public:
};

#endif //PARSER_LEQ_H

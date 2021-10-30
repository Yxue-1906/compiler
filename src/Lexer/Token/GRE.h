//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRE_H
#define PARSER_GRE_H


class GRE : public Token<std::string> {
private:
public:
    GRE() : Token(TokenBase::GRE,
                  std::make_shared<std::string>(">")) {}

public:
};

#endif //PARSER_GRE_H

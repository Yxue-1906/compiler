//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GEQ_H
#define PARSER_GEQ_H


class GEQ : public Token<std::string> {
private:
public:
    GEQ() : Token(TokenBase::GEQ,
                  std::make_shared<std::string>(">=")) {}

public:
};

#endif //PARSER_GEQ_H

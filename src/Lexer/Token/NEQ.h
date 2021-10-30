//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_NEQ_H
#define PARSER_NEQ_H


class NEQ : public Token<std::string> {
private:
public:
    NEQ() : Token(TokenBase::NEQ,
                  std::make_shared<std::string>("!=")) {}

public:
};

#endif //PARSER_NEQ_H

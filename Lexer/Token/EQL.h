//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_EQL_H
#define PARSER_EQL_H


class EQL : public Token {
private:
public:
    EQL() : Token(Token::EQL) {
        setValue_p(new std::string("=="));
    }

public:
};

#endif //PARSER_EQL_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LEQ_H
#define PARSER_LEQ_H


class LEQ : public Token {
private:
public:
    LEQ() : Token(Token::LEQ) {
        setValue_p(new std::string("<="));
    }

public:
};

#endif //PARSER_LEQ_H

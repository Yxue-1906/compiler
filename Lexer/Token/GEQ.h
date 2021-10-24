//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GEQ_H
#define PARSER_GEQ_H


class GEQ : public Token {
private:
public:
    GEQ() : Token(Token::GEQ) {
        setValue_p(new std::string(">="));
    }

public:
};

#endif //PARSER_GEQ_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRE_H
#define PARSER_GRE_H


class GRE : public Token {
private:
public:
    GRE() : Token(Token::GRE) {
        setValue_p(new std::string(">"));
    }

public:
};

#endif //PARSER_GRE_H

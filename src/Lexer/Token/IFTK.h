//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_IFTK_H
#define PARSER_IFTK_H


class IFTK : public Token {
private:
public:
    IFTK() : Token(Token::IFTK) {
        setValue_p(new std::string("if"));
    }

public:
};


#endif //PARSER_IFTK_H

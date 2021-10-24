//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RETURNTK_H
#define PARSER_RETURNTK_H


class RETURNTK : public Token {
private:
public:
    RETURNTK() : Token(Token::RETURNTK) {
    setValue_p(new std::string("return"));}

public:
};

#endif //PARSER_RETURNTK_H

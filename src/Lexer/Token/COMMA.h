//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_COMMA_H
#define PARSER_COMMA_H


class COMMA : public Token {
private:
public:
    COMMA() : Token(Token::COMMA) {
        setValue_p(new std::string(","));
    }

public:
};

#endif //PARSER_COMMA_H

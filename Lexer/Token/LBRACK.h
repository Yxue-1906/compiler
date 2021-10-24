//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LBRACK_H
#define PARSER_LBRACK_H


class LBRACK : public Token {
private:
public:
    LBRACK() : Token(Token::LBRACK) {
        setValue_p(new std::string("["));
    }

public:
};

#endif //PARSER_LBRACK_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_INTCON_H
#define PARSER_INTCON_H


class INTCON : public Token {
private:
public:
    INTCON(int value) : Token(Token::INTCON) {
        setValue_p(new int{value});
    }

public:
};


#endif //PARSER_INTCON_H

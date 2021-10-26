//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_BREAKTK_H
#define PARSER_BREAKTK_H


class BREAKTK : public Token {
private:
public:
    BREAKTK() : Token(Token::BREAKTK) {
        setValue_p(new std::string("break"));
    }

public:
};


#endif //PARSER_BREAKTK_H

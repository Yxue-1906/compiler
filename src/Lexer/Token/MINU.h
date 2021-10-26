//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MINU_H
#define PARSER_MINU_H

class MINU : public Token {
private:
public:
    MINU() : Token(Token::MINU) {
        setValue_p(new std::string("-"));
    }

public:
};

#endif //PARSER_MINU_H

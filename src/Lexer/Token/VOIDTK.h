//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_VOIDTK_H
#define PARSER_VOIDTK_H


class VOIDTK : public Token {
private:
public:
    VOIDTK() : Token(Token::VOIDTK) {
        setValue_p(new std::string("void"));
    }

public:
    \

};

#endif //PARSER_VOIDTK_H

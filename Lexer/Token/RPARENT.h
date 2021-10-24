//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RPARENT_H
#define PARSER_RPARENT_H


class RPARENT : public Token {
private:
public:
    RPARENT() : Token(Token::RPARENT) {
    setValue_p(new std::string(")"));}

public:
};

#endif //PARSER_RPARENT_H

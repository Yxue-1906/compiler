//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LPARENT_H
#define PARSER_LPARENT_H


class LPARENT : public Token {
private:
public:
    LPARENT() : Token(Token::LPARENT) {
    setValue_p(new std::string("("));}

public:
};


#endif //PARSER_LPARENT_H

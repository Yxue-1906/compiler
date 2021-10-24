//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MAINTK_H
#define PARSER_MAINTK_H


class MAINTK : public Token {
private:
public:
    MAINTK() : Token(Token::MAINTK) {
    setValue_p(new std::string("main"));}

public:
};



#endif //PARSER_MAINTK_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_PRINTFTK_H
#define PARSER_PRINTFTK_H


class PRINTFTK: public Token {
private:
public:
    PRINTFTK():Token(Token::PRINTFTK){
    setValue_p(new std::string("printf"));}

public:
};


#endif //PARSER_PRINTFTK_H

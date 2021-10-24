//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MULT_H
#define PARSER_MULT_H

class MULT : public Token {
private:
public:
    MULT() : Token(Token::MULT){
    setValue_p(new std::string("*"));}

public:
};

#endif //PARSER_MULT_H

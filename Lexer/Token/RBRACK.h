//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RBRACK_H
#define PARSER_RBRACK_H


class RBRACK : public Token {
private:
public:
    RBRACK() : Token(Token::RBRACK){
    setValue_p(new std::string("]"));}

public:
};


#endif //PARSER_RBRACK_H

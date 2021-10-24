//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MOD_H
#define PARSER_MOD_H


class MOD : public Token {
private:
public:
    MOD() : Token(Token::MOD) {
    setValue_p(new std::string("%"));}

public:
};

#endif //PARSER_MOD_H

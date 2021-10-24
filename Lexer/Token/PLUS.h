//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_PLUS_H
#define PARSER_PLUS_H

class PLUS : public Token {
private:
public:
    PLUS() : Token(Token::PLUS) {
    setValue_p(new std::string("+"));}

public:
};


#endif //PARSER_PLUS_H

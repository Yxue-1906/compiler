//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_NEQ_H
#define PARSER_NEQ_H


class NEQ : public Token {
private:
public:
    NEQ() : Token(Token::NEQ) {
    setValue_p(new std::string("!="));}

public:
};

#endif //PARSER_NEQ_H

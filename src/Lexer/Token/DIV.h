//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_DIV_H
#define PARSER_DIV_H


class DIV : public Token {
private:
public:
    DIV() : Token(Token::DIV) {
        setValue_p(new std::string("/"));
    }

public:
};


#endif //PARSER_DIV_H

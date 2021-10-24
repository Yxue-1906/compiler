//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_ASSIGN_H
#define PARSER_ASSIGN_H


class ASSIGN : public Token {
private:
public:
    ASSIGN() : Token(Token::ASSIGN) {
        setValue_p(new std::string("="));
    }

public:
};

#endif //PARSER_ASSIGN_H

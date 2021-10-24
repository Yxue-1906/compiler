//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_SEMICN_H
#define PARSER_SEMICN_H


class SEMICN : public Token {
private:
public:
    SEMICN() : Token(Token::SEMICN) {
        setValue_p(new std::string(";"));
    }

public:
};


#endif //PARSER_SEMICN_H

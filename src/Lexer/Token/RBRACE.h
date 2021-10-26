//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RBRACE_H
#define PARSER_RBRACE_H


class RBRACE : public Token {
private:
public:
    RBRACE() : Token(Token::RBRACE) {
        setValue_p(new std::string("}"));
    }

public:
};

#endif //PARSER_RBRACE_H

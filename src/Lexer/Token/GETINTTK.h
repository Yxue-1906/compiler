//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GETINTTK_H
#define PARSER_GETINTTK_H


class GETINTTK : public Token {
private:
public:
    GETINTTK() : Token(Token::GETINTTK) {
        setValue_p(new std::string("getint"));
    }

public:
};


#endif //PARSER_GETINTTK_H

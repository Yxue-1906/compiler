//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_INTTK_H
#define PARSER_INTTK_H


class INTTK : public Token {
private:
public:
    INTTK() : Token(Token::INTTK) {
        setValue_p(new std::string("int"));
    }

public:
};


#endif //PARSER_INTTK_H

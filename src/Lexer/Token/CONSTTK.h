//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_CONSTTK_H
#define PARSER_CONSTTK_H


class CONSTTK : public Token {
private:
public:
    CONSTTK() : Token(Token::CONSTTK) {
        setValue_p(new std::string("const"));
    }

public:
};


#endif //PARSER_CONSTTK_H

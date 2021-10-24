//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_ELSETK_H
#define PARSER_ELSETK_H


class ELSETK : public Token {
private:
public:
    ELSETK() : Token(Token::ELSETK) {
        setValue_p(new std::string("else"));
    }

public:
};


#endif //PARSER_ELSETK_H

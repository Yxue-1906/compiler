//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_NOT_H
#define PARSER_NOT_H


class NOT : public Token {
private:
public:
    NOT() : Token(Token::NOT) {
        setValue_p(new std::string("!"));
    }

public:
};


#endif //PARSER_NOT_H

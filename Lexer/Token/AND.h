//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_AND_H
#define PARSER_AND_H


class AND : public Token {
private:

public:
    AND() : Token(Token::AND) {
        setValue_p(new std::string("&&"));
    }

public:
};


#endif //PARSER_AND_H

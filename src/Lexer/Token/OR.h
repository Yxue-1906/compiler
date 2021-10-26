//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_OR_H
#define PARSER_OR_H


class OR : public Token {
private:
public:
    OR() : Token(Token::OR) {
        setValue_p(new std::string("||"));
    }

public:
};


#endif //PARSER_OR_H

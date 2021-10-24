//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_WHILETK_H
#define PARSER_WHILETK_H


class WHILETK : public Token {
private:
public:
    WHILETK() : Token(Token::WHILETK) {
        setValue_p(new std::string("while"));
    }

public:
};


#endif //PARSER_WHILETK_H

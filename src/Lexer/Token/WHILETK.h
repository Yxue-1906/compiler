//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_WHILETK_H
#define PARSER_WHILETK_H


class WHILETK : public Token<std::string> {
private:
public:
    WHILETK() : Token(TokenBase::WHILETK,
                      std::make_shared<std::string>("while")) {}

public:
};


#endif //PARSER_WHILETK_H

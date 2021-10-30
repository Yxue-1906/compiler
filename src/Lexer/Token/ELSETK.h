//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_ELSETK_H
#define PARSER_ELSETK_H


class ELSETK : public Token<std::string> {
private:
public:
    ELSETK() : Token(TokenBase::ELSETK,
                     std::make_shared<std::string>("else")) {}

public:
};


#endif //PARSER_ELSETK_H

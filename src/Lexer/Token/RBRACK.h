//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RBRACK_H
#define PARSER_RBRACK_H


class RBRACK : public Token<std::string> {
private:
public:
    RBRACK() : Token(TokenBase::RBRACK,
                     std::make_shared<std::string>("]")) {}

public:
};


#endif //PARSER_RBRACK_H

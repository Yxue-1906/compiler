//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_SEMICN_H
#define PARSER_SEMICN_H


class SEMICN : public Token<std::string> {
private:
public:
    SEMICN() : Token(TokenBase::SEMICN,
                     std::make_shared<std::string>(";")) {}

public:
};


#endif //PARSER_SEMICN_H

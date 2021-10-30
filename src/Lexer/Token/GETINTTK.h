//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GETINTTK_H
#define PARSER_GETINTTK_H


class GETINTTK : public Token<std::string> {
private:
public:
    GETINTTK() : Token(TokenBase::GETINTTK,
                       std::make_shared<std::string>("getint")) {}

public:
};


#endif //PARSER_GETINTTK_H

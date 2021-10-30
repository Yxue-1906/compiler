//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_CONSTTK_H
#define PARSER_CONSTTK_H


class CONSTTK : public Token<std::string> {
private:
public:
    CONSTTK() : Token(TokenBase::CONSTTK,
                      std::make_shared<std::string>("const")) {}

public:
};


#endif //PARSER_CONSTTK_H

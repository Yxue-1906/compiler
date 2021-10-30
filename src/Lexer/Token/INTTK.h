//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_INTTK_H
#define PARSER_INTTK_H


class INTTK : public Token<std::string> {
private:
public:
    INTTK() : Token(TokenBase::INTTK,
                    std::make_shared<std::string>("int")) {}

public:
};


#endif //PARSER_INTTK_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_CONTINUETK_H
#define PARSER_CONTINUETK_H


class CONTINUETK : public Token<std::string> {
private:
public:
    CONTINUETK() : Token(TokenBase::CONTINUETK,
                         std::make_shared<std::string>("continue")) {}

public:
};


#endif //PARSER_CONTINUETK_H

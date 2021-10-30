//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LPARENT_H
#define PARSER_LPARENT_H


class LPARENT : public Token<std::string> {
private:
public:
    LPARENT() : Token(TokenBase::LPARENT,
                      std::make_shared<std::string>("(")) {}

public:
};


#endif //PARSER_LPARENT_H

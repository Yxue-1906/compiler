//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RPARENT_H
#define PARSER_RPARENT_H


class RPARENT : public Token<std::string> {
private:
public:
    RPARENT() : Token(TokenBase::RPARENT,
                      std::make_shared<std::string>(")")) {}

public:
};

#endif //PARSER_RPARENT_H

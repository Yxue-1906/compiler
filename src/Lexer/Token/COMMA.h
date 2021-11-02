//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_COMMA_H
#define PARSER_COMMA_H


class COMMA : public Token<std::string> {
private:
public:
    COMMA() : Token(TokenBase::COMMA,
                    std::make_shared<std::string>(",")) {}

public:
};

#endif //PARSER_COMMA_H

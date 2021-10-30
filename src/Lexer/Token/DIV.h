//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_DIV_H
#define PARSER_DIV_H


class DIV : public Token<std::string> {
private:
public:
    DIV() : Token(TokenBase::DIV,
                  std::make_shared<std::string>("/")) {}

public:
};


#endif //PARSER_DIV_H

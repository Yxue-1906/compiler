//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_NOT_H
#define PARSER_NOT_H


class NOT : public Token<std::string> {
private:
public:
    NOT() : Token(TokenBase::NOT,
                  std::make_shared<std::string>("!")) {}

public:
};


#endif //PARSER_NOT_H

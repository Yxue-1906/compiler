//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_AND_H
#define PARSER_AND_H


class AND : public Token<std::string> {
private:

public:
    AND() : Token(TokenBase::AND,
                  std::make_shared<std::string>("&&")) {}

public:
};


#endif //PARSER_AND_H

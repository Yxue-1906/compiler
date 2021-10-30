//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MOD_H
#define PARSER_MOD_H


class MOD : public Token<std::string> {
private:
public:
    MOD() : Token(TokenBase::MOD,
                  std::make_shared<std::string>("%")) {}

public:
};

#endif //PARSER_MOD_H

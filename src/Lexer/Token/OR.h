//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_OR_H
#define PARSER_OR_H


class OR : public Token<std::string> {
private:
public:
    OR() : Token(TokenBase::OR,
                 std::make_shared<std::string>("||")) {}

public:
};


#endif //PARSER_OR_H

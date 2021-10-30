//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LBRACE_H
#define PARSER_LBRACE_H


class LBRACE : public Token<std::string> {
private:
public:
    LBRACE() : Token(TokenBase::LBRACE,
                     std::make_shared<std::string>("{")) {}

public:
};


#endif //PARSER_LBRACE_H

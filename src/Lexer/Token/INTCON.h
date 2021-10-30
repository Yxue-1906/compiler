//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_INTCON_H
#define PARSER_INTCON_H


class INTCON : public Token<int> {
private:
public:
    INTCON(int value) : Token(TokenBase::INTCON,
                              std::make_shared<int>(value)) {}

public:
};


#endif //PARSER_INTCON_H

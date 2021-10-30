//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_PLUS_H
#define PARSER_PLUS_H

class PLUS : public Token<std::string> {
private:
public:
    PLUS() : Token(TokenBase::PLUS,
                   std::make_shared<std::string>("+")) {}

public:
};


#endif //PARSER_PLUS_H

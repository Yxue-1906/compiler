//
// Created by unrelated on 2021/9/29.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H


#include <string>

class Token {
public:
    virtual const std::string getLabel();

private:
};


#endif //LEXER_TOKEN_H

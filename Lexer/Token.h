//
// Created by unrelated on 2021/10/17.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H


#include <map>
#include "../Output/MyOutput.h"

class Token : public MyOutput {
private:
    const std::string tokenName;
    const int tokenType;

public:
    static const std::map<int, std::string> type2Name;

public:
    Token(int);

    std::string &getTokenName();

    static int getTokenType(Token&);

private:


};


#endif //LEXER_TOKEN_H

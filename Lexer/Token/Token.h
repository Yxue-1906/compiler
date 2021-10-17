//
// Created by unrelated on 2021/10/17.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H


#include <map>
#include "../../Output/MyOutput.h"

class Token : public MyOutput {
private:
    static const std::map<int, std::string> type2Name;

    const std::string tokenName;
    const int tokenType;
public:
    Token(int);

private:

protected:
    std::string &getTokenName();

    int getTokenType();

};


#endif //LEXER_TOKEN_H

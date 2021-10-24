//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LSS_H
#define PARSER_LSS_H


class LSS : public Token {
private:
public:
    LSS() : Token(Token::LSS){
    setValue_p(new std::string("<"));}

public:
};

#endif //PARSER_LSS_H

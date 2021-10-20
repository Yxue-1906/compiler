//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_SEMICN_H
#define PARSER_SEMICN_H


class SEMICN : public Token {
private:
    const std::string value;
public:
    SEMICN() : Token(Token::SEMICN), value(";") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_SEMICN_H

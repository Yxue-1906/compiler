//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_EQL_H
#define PARSER_EQL_H


class EQL : public Token {
private:
    const std::string value;
public:
    EQL() : Token(Token::EQL), value("==") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_EQL_H

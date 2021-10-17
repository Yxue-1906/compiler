//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_IFTK_H
#define PARSER_IFTK_H


class IFTK: public Token {
private:
    const std::string value;
public:
    IFTK() : Token(9), value("if") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_IFTK_H

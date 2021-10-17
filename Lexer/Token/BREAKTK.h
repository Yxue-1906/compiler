//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_BREAKTK_H
#define PARSER_BREAKTK_H


class BREAKTK: public Token {
private:
    const std::string value;
public:
    BREAKTK() : Token(7), value("break") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_BREAKTK_H

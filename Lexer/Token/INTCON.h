//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_INTCON_H
#define PARSER_INTCON_H


class INTCON : public Token {
private:
    const int value;
public:
    INTCON(int value) : Token(2), value(value) {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};



#endif //PARSER_INTCON_H

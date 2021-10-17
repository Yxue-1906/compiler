//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MULT_H
#define PARSER_MULT_H

class MULT : public Token {
private:
    const std::string value;
public:
    MULT() : Token(21), value("*") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_MULT_H

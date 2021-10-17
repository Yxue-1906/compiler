//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MINU_H
#define PARSER_MINU_H

class MINU : public Token {
private:
    const std::string value;
public:
    MINU() : Token(19), value("-") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_MINU_H

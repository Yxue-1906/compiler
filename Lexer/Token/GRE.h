//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GRE_H
#define PARSER_GRE_H


class GRE : public Token {
private:
    const std::string value;
public:
    GRE() : Token(26), value(">") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = std::move(getOfs());
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_GRE_H

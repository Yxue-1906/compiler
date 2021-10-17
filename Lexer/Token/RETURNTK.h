//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RETURNTK_H
#define PARSER_RETURNTK_H


class RETURNTK : public Token {
private:
    const std::string value;
public:
    RETURNTK() : Token(17), value("return") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = std::move(getOfs());
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_RETURNTK_H

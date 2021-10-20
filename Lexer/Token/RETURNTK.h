//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RETURNTK_H
#define PARSER_RETURNTK_H


class RETURNTK : public Token {
private:
    const std::string value;
public:
    RETURNTK() : Token(Token::RETURNTK), value("return") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_RETURNTK_H

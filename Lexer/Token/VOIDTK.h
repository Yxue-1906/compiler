//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_VOIDTK_H
#define PARSER_VOIDTK_H


class VOIDTK : public Token {
private:
    const std::string value;
public:
    VOIDTK() : Token(20), value("void") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_VOIDTK_H

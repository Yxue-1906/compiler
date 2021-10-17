//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_WHILETK_H
#define PARSER_WHILETK_H


class WHILETK: public Token {
private:
    const std::string value;
public:
    WHILETK() : Token(14), value("while") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_WHILETK_H

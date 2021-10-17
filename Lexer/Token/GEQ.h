//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GEQ_H
#define PARSER_GEQ_H


class GEQ : public Token {
private:
    const std::string value;
public:
    GEQ() : Token(27), value(">=") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_GEQ_H

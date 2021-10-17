//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LEQ_H
#define PARSER_LEQ_H


class LEQ : public Token {
private:
    const std::string value;
public:
    LEQ() : Token(25), value("<=") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_LEQ_H

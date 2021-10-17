//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_DIV_H
#define PARSER_DIV_H


class DIV : public Token {
private:
    const std::string value;
public:
    DIV() : Token(22), value("/") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_DIV_H

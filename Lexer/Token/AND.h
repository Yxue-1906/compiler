//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_AND_H
#define PARSER_AND_H


class AND: public Token {
private:
    const std::string value;
public:
    AND() : Token(12), value("&&") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = std::move(getOfs());
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_AND_H

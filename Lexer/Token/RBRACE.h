//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RBRACE_H
#define PARSER_RBRACE_H


class RBRACE : public Token {
private:
    const std::string value;
public:
    RBRACE() : Token(38), value("}") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_RBRACE_H

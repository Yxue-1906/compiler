//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LBRACE_H
#define PARSER_LBRACE_H


class LBRACE : public Token {
private:
    const std::string value;
public:
    LBRACE() : Token(37), value("{") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_LBRACE_H

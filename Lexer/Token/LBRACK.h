//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LBRACK_H
#define PARSER_LBRACK_H


class LBRACK : public Token {
private:
    const std::string value;
public:
    LBRACK() : Token(35), value("[") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = std::move(getOfs());
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_LBRACK_H

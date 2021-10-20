//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MOD_H
#define PARSER_MOD_H


class MOD : public Token {
private:
    const std::string value;
public:
    MOD() : Token(Token::MOD), value("%") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_MOD_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_ASSIGN_H
#define PARSER_ASSIGN_H


class ASSIGN : public Token {
private:
    const std::string value;
public:
    ASSIGN() : Token(Token::ASSIGN), value("=") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_ASSIGN_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RPARENT_H
#define PARSER_RPARENT_H


class RPARENT : public Token {
private:
    const std::string value;
public:
    RPARENT() : Token(Token::RPARENT), value(")") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_RPARENT_H

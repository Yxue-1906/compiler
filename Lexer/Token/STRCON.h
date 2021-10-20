//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_STRCON_H
#define PARSER_STRCON_H


class STRCON : public Token {
private:
    const std::string value;
public:
    STRCON(std::string value) : Token(Token::STRCON), value(std::move(value)) {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_STRCON_H

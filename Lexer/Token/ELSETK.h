//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_ELSETK_H
#define PARSER_ELSETK_H


class ELSETK : public Token {
private:
    const std::string value;
public:
    ELSETK() : Token(Token::ELSETK), value("else") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_ELSETK_H

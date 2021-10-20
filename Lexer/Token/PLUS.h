//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_PLUS_H
#define PARSER_PLUS_H

class PLUS : public Token {
private:
    const std::string value;
public:
    PLUS() : Token(Token::PLUS), value("+") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_PLUS_H

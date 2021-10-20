//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_PRINTFTK_H
#define PARSER_PRINTFTK_H


class PRINTFTK: public Token {
private:
    const std::string value;
public:
    PRINTFTK():Token(Token::PRINTFTK), value("printf"){}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs<<getTokenName()<<' ' <<value<<std::endl;
    }
};


#endif //PARSER_PRINTFTK_H

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_GETINTTK_H
#define PARSER_GETINTTK_H


class GETINTTK : public Token {
private:
    const std::string value;
public:
    GETINTTK() : Token(Token::GETINTTK), value("getint") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_GETINTTK_H

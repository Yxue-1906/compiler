//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_INTTK_H
#define PARSER_INTTK_H


class INTTK : public Token {
private:
    const std::string value;
public:
    INTTK() : Token(6), value("int") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_INTTK_H

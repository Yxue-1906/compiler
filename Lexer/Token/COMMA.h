//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_COMMA_H
#define PARSER_COMMA_H


class COMMA : public Token {
private:
    const std::string value;
public:
    COMMA() : Token(32), value(",") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_COMMA_H

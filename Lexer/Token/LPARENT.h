//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LPARENT_H
#define PARSER_LPARENT_H


class LPARENT : public Token {
private:
    const std::string value;
public:
    LPARENT() : Token(33), value("(") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = std::move(getOfs());
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_LPARENT_H

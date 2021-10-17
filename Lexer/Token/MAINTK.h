//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_MAINTK_H
#define PARSER_MAINTK_H


class MAINTK : public Token {
private:
    const std::string value;
public:
    MAINTK() : Token(4), value("main") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = std::move(getOfs());
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};



#endif //PARSER_MAINTK_H
